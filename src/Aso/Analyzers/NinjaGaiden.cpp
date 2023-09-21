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

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
int NinjaGaidenAnalyzer::index = -1;

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
    //
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
    return position.x >= Config::geti(aso::NinjaGaidenConfigKey::HUD::xMin) &&
           position.x <= Config::geti(aso::NinjaGaidenConfigKey::HUD::xMax) &&
           position.y >= Config::geti(aso::NinjaGaidenConfigKey::HUD::yMin) &&
           position.y <= Config::geti(aso::NinjaGaidenConfigKey::HUD::yMax);
}

}
