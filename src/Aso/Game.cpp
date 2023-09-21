/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Game.hpp>
#include <Aso/Config.hpp>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

int aso::GameConfigKey::xMin = -1;
int aso::GameConfigKey::xMax = -1;
int aso::GameConfigKey::yMin = -1;
int aso::GameConfigKey::yMax = -1;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso
{

/**
 *
 */
Game::Game() : _analyzerCount(0)
{
    aso::GameConfigKey::xMin = Config::insert(260);
    aso::GameConfigKey::xMax = Config::insert(1660);
    aso::GameConfigKey::yMin = Config::insert(0);
    aso::GameConfigKey::yMax = Config::insert(1080);
}

/**
 *
 */
void Game::__dispatch(Point position, const unsigned char *color)
{
    for (std::uint8_t i = 0; i < _analyzerCount; i++)
    {
        _analyzers[i]->analyze(position, color);
    }
}

/**
 *
 */
Event Game::poll()
{
    Event event;

    for (std::uint8_t i = 0; i < _analyzerCount; i++)
    {
        if ((event = _analyzers[i]->poll()))
        {
            return event;
        }
    }

    return event;
}

/**
 *
 */
void Game::updateFromCaptureFrame(const cv::Mat &frame)
{
    for (std::uint8_t i = 0; i < _analyzerCount; i++)
    {
        _analyzers[i]->reset();
    }

    for (int i = 0, j = 0; i < frame.rows * frame.cols * 3; i += 3, j++)
    {
        int x = j % frame.cols;
        int y = j / frame.cols;

        if (x >= Config::geti(aso::GameConfigKey::xMin) &&
            x <= Config::geti(aso::GameConfigKey::xMax) &&
            y >= Config::geti(aso::GameConfigKey::yMin) &&
            y <= Config::geti(aso::GameConfigKey::yMax))
        {
            __dispatch({x, y}, frame.data + i);
        }
    }

    for (std::uint8_t i = 0; i < _analyzerCount; i++)
    {
        _analyzers[i]->conclude();
        _analyzers[i]->dispatch();
    }
}

}
