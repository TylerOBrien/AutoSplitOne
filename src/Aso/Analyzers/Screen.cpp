/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Analyzers/Screen.hpp>
#include <Aso/Graphics/Color.hpp>
#include <Aso/Math/Point.hpp>

/*
|--------------------------------------------------------------------------
| Preprocesser
|--------------------------------------------------------------------------
*/

#define SCREEN_X 475
#define SCREEN_Y 13
#define SCREEN_W 1324
#define SCREEN_H 1054

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

aso::Color _aso_screen_min = {255, 255, 255};
aso::Color _aso_screen_max = {0, 0, 0};

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
int ScreenAnalyzer::index = -1;

/**
 *
 */
ScreenAnalyzer::ScreenAnalyzer()
{
    //
}

/**
 *
 */
Event ScreenAnalyzer::poll()
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
void ScreenAnalyzer::reset()
{
    _previousState        = _currentState;
    _currentState.isBlack = false;
    _currentState.isWhite = false;

    _aso_screen_min = {255, 255, 255};
    _aso_screen_max = {0, 0, 0};
}

/**
 *
 */
void ScreenAnalyzer::analyze(Point position, int index, const unsigned char *color)
{
    if (_aso_screen_min.r > color[2])
    {
        _aso_screen_min.r = color[2];
    }

    if (_aso_screen_max.r < color[2])
    {
        _aso_screen_max.r = color[2];
    }

    if (_aso_screen_min.g > color[1])
    {
        _aso_screen_min.g = color[1];
    }

    if (_aso_screen_max.g < color[1])
    {
        _aso_screen_max.g = color[1];
    }

    if (_aso_screen_min.b > color[0])
    {
        _aso_screen_min.b = color[0];
    }

    if (_aso_screen_max.b < color[0])
    {
        _aso_screen_max.b = color[0];
    }
}

/**
 *
 */
void ScreenAnalyzer::conclude()
{
    _currentState.isBlack = (
        _aso_screen_max.r < 32 &&
        _aso_screen_max.g < 32 &&
        _aso_screen_max.b < 32
    );

    _currentState.isWhite = (
        _aso_screen_min.r > 224 &&
        _aso_screen_min.g > 224 &&
        _aso_screen_min.b > 224
    );
}

/**
 *
 */
ScreenState ScreenAnalyzer::state() const
{
    return _currentState;
}


/**
 *
 */
void ScreenAnalyzer::dispatch()
{
    if (_currentState.isBlack)
    {
        if (!_previousState.isBlack)
        {
            _events.push(ScreenEvent::BLACK);
        }
    }
    else if (_previousState.isBlack)
    {
        _events.push(ScreenEvent::UNBLACK);
    }

    if (_currentState.isWhite)
    {
        if (!_previousState.isWhite)
        {
            _events.push(ScreenEvent::WHITE);
        }
    }
    else if (_previousState.isWhite)
    {
        _events.push(ScreenEvent::UNWHITE);
    }
}

}
