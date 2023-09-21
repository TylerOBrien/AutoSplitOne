/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Analyzers/NinjaGaiden.hpp>
#include <Aso/Config.hpp>
#include <Aso/Graphics/Color.hpp>
#include <Aso/Math/Point.hpp>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

int aso::NinjaGaidenConfigKey::HUD::xMin = -1;
int aso::NinjaGaidenConfigKey::HUD::xMax = -1;
int aso::NinjaGaidenConfigKey::HUD::yMin = -1;
int aso::NinjaGaidenConfigKey::HUD::yMax = -1;

int aso::NinjaGaidenAnalyzer::index = -1;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
int NinjaGaidenConfig::HUD::xMin()
{
    return Config::geti(aso::NinjaGaidenConfigKey::HUD::xMin);
}

/**
 *
 */
int NinjaGaidenConfig::HUD::yMin()
{
    return Config::geti(aso::NinjaGaidenConfigKey::HUD::yMin);
}

/**
 *
 */
int NinjaGaidenConfig::HUD::xMax()
{
    return Config::geti(aso::NinjaGaidenConfigKey::HUD::xMax);
}

/**
 *
 */
int NinjaGaidenConfig::HUD::yMax()
{
    return Config::geti(aso::NinjaGaidenConfigKey::HUD::yMax);
}

/**
 *
 */
int NinjaGaidenConfig::HUD::width()
{
    return xMax() - xMin();
}

/**
 *
 */
int NinjaGaidenConfig::HUD::height()
{
    return yMax() - yMin();
}

/**
 *
 */
NinjaGaidenAnalyzer::NinjaGaidenAnalyzer()
{
    aso::NinjaGaidenConfigKey::HUD::xMin = Config::insert(440);
    aso::NinjaGaidenConfigKey::HUD::xMax = Config::insert(440 + 1062);
    aso::NinjaGaidenConfigKey::HUD::yMin = Config::insert(104);
    aso::NinjaGaidenConfigKey::HUD::yMax = Config::insert(104 + 110);
}

/**
 *
 */
Event NinjaGaidenAnalyzer::poll()
{
    static Event event;

    if (_events.empty())
    {
        event.type = Event::None;
    }
    else
    {
        event.type = _events.front();
        _events.pop();
    }

    return event;
}

/**
 *
 */
void NinjaGaidenAnalyzer::reset()
{
    //
}

/**
 *
 */
void NinjaGaidenAnalyzer::analyze(Point position, const unsigned char *color)
{
    if (isWithinKnownZero(position))
    {
        //
    }

    if (isWithinTimerFirstDigit(position))
    {
        //
    }

    if (isWithinTimerSecondDigit(position))
    {
        //
    }

    if (isWithinTimerThirdDigit(position))
    {
        //
    }
}

/**
 *
 */
void NinjaGaidenAnalyzer::conclude()
{
    //
}

/**
 *
 */
void NinjaGaidenAnalyzer::dispatch()
{
    //
}

/**
 *
 */
bool NinjaGaidenAnalyzer::isWithinHUD(Point position) const
{
    return position.x >= NinjaGaidenConfig::HUD::xMin() &&
           position.x <= NinjaGaidenConfig::HUD::xMax() &&
           position.y >= NinjaGaidenConfig::HUD::yMin() &&
           position.y <= NinjaGaidenConfig::HUD::yMax();
}

/**
 *
 */
bool NinjaGaidenAnalyzer::isWithinKnownZero(Point position) const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return position.x >= (xMin + (tileWidth * 2)) &&
           position.x <= (xMin + (tileWidth * 3)) &&
           position.y >= (yMin + (tileHeight * 2)) &&
           position.y <= (yMin + (tileHeight * 2));
}

/**
 *
 */
bool NinjaGaidenAnalyzer::isWithinTimerFirstDigit(Point position) const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return position.x >= (xMin + (tileWidth * 6)) &&
           position.x <= (xMin + (tileWidth * 7)) &&
           position.y >= (yMin + (tileHeight * 1)) &&
           position.y <= (yMin + (tileHeight * 2));
}

/**
 *
 */
bool NinjaGaidenAnalyzer::isWithinTimerSecondDigit(Point position) const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return position.x >= (xMin + (tileWidth * 7)) &&
           position.x <= (xMin + (tileWidth * 8)) &&
           position.y >= (yMin + (tileHeight * 1)) &&
           position.y <= (yMin + (tileHeight * 2));
}

/**
 *
 */
bool NinjaGaidenAnalyzer::isWithinTimerThirdDigit(Point position) const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return position.x >= (xMin + (tileWidth * 8)) &&
           position.x <= (xMin + (tileWidth * 9)) &&
           position.y >= (yMin + (tileHeight * 1)) &&
           position.y <= (yMin + (tileHeight * 2));
}

}
