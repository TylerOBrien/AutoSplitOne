/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Game.hpp>
#include <Aso/Config.hpp>

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
Game::Game()
    : _analyzerCount(0)
{}

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

        if (x >= Config::GAME_X &&
            x <= Config::GAME_XMAX &&
            y >= Config::GAME_Y &&
            y <= Config::GAME_YMAX)
        {
            __dispatch({x, y}, frame.data + i);
        }
    }

    for (std::uint8_t i = 0; i < _analyzerCount; i++)
    {
        _analyzers[i]->conclude();
    }
}

}
