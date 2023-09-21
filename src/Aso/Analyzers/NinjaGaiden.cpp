/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Analyzers/NinjaGaiden.hpp>
#include <Aso/Config.hpp>
#include <Aso/Graphics/Color.hpp>
#include <Aso/Math/Point.hpp>

#include <cstdlib>

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

int _aso_ninja_gaiden_timer_diff_sum[3] = {-1};

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
    aso::NinjaGaidenConfigKey::HUD::xMin = Config::insert(439);
    aso::NinjaGaidenConfigKey::HUD::xMax = Config::insert(439 + 1062);
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
    _previousState = _currentState;
    _currentState.isTimerZero = false;
    _aso_ninja_gaiden_timer_diff_sum[0] = -1;
    _aso_ninja_gaiden_timer_diff_sum[1] = -1;
    _aso_ninja_gaiden_timer_diff_sum[2] = -1;
}

/**
 *
 */
void NinjaGaidenAnalyzer::analyze(Point position, int index, const unsigned char *color)
{
    if (!isWithinHUD(position))
    {
        return;
    }

    const BGR *head  = (BGR*)(color - index);
    const BGR *white = head + knownZeroWhitePixelIndex();

    if (white[0].r < 200 &&
        white[0].g < 200 &&
        white[0].b < 200)
    {
        return;
    }

    int digit = -1;

    if (isWithinTimerFirstDigit(position))
    {
        digit = 0;
    }

    if (isWithinTimerSecondDigit(position))
    {
        digit = 1;
    }

    if (isWithinTimerThirdDigit(position))
    {
        digit = 2;
    }

    if (digit != -1)
    {
        Point topLeft = (digit == 0)
                        ? timerFirstDigitPosition()  : (digit == 1)
                        ? timerSecondDigitPosition() : timerThirdDigitPosition();

        Point relative = {position.x - topLeft.x, position.y - topLeft.y};
        int offset = (relative.y * 1920 + relative.x) + knownZeroIndex();

        _aso_ninja_gaiden_timer_diff_sum[digit] += abs(color[0] - head[offset].b);
        _aso_ninja_gaiden_timer_diff_sum[digit] += abs(color[1] - head[offset].g);
        _aso_ninja_gaiden_timer_diff_sum[digit] += abs(color[2] - head[offset].r);
    }
}

/**
 *
 */
void NinjaGaidenAnalyzer::conclude()
{
    _currentState.isTimerZero = (
        _aso_ninja_gaiden_timer_diff_sum[0] != -1 &&
        _aso_ninja_gaiden_timer_diff_sum[1] != -1 &&
        _aso_ninja_gaiden_timer_diff_sum[1] != -1 &&
        _aso_ninja_gaiden_timer_diff_sum[0] < 220000 &&
        _aso_ninja_gaiden_timer_diff_sum[1] < 220000 &&
        _aso_ninja_gaiden_timer_diff_sum[2] < 220000
    );
}

/**
 *
 */
void NinjaGaidenAnalyzer::dispatch()
{
    if (_currentState.isTimerZero && !_previousState.isTimerZero)
    {
        _events.push(NinjaGaidenEvent::TIMER_ZERO);
    }
}

/**
 *
 */
int NinjaGaidenAnalyzer::knownZeroIndex() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return ((yMin + (tileHeight * 2)) * 1920) + xMin + (tileWidth * 2);
}

/**
 *
 */
int NinjaGaidenAnalyzer::knownZeroWhitePixelIndex() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return (((yMin + 8) + (tileHeight * 2)) * 1920) + (xMin + 4) + (tileWidth * 2);
}

/**
 *
 */
Point NinjaGaidenAnalyzer::knownZeroPosition() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return Point(xMin + (tileWidth * 2), yMin + (tileHeight * 2));
}

/**
 *
 */
Rect NinjaGaidenAnalyzer::knownZeroSize() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    return Rect((xMax - xMin) / 27, (yMax - yMin) / 3);
}

/**
 *
 */
Point NinjaGaidenAnalyzer::timerFirstDigitPosition() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return Point(xMin + (tileWidth * 6), yMin + (tileHeight * 1));
}

/**
 *
 */
Point NinjaGaidenAnalyzer::timerSecondDigitPosition() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return Point(xMin + (tileWidth * 7), yMin + (tileHeight * 1));
}

/**
 *
 */
Point NinjaGaidenAnalyzer::timerThirdDigitPosition() const
{
    int xMin = NinjaGaidenConfig::HUD::xMin();
    int xMax = NinjaGaidenConfig::HUD::xMax();
    int yMin = NinjaGaidenConfig::HUD::yMin();
    int yMax = NinjaGaidenConfig::HUD::yMax();

    int tileWidth  = (xMax - xMin) / 27;
    int tileHeight = (yMax - yMin) / 3;

    return Point(xMin + (tileWidth * 8), yMin + (tileHeight * 1));
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
