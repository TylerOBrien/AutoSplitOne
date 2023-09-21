/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Analyzers/EverDriveN8.hpp>
#include <Aso/Config.hpp>
#include <Aso/Math/Math.hpp>
#include <Aso/Math/Point.hpp>

/*
|--------------------------------------------------------------------------
| Config
|--------------------------------------------------------------------------
*/

enum EverDriveN8Config {
    MENU_WIDTH  = 510,
    MENU_HEIGHT = 494,
};

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

aso::Point _aso_edn8_menu_top_left     = {-1, -1};
aso::Point _aso_edn8_menu_top_right    = {-1, -1};
aso::Point _aso_edn8_menu_bottom_left  = {-1, -1};
aso::Point _aso_edn8_menu_bottom_right = {-1, -1};

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
int EverDriveN8Analyzer::index = -1;

/**
 *
 */
EverDriveN8Analyzer::EverDriveN8Analyzer()
{
    //
}

/**
 *
 */
Event EverDriveN8Analyzer::poll()
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
void EverDriveN8Analyzer::reset()
{
    _previousState              = _currentState;
    _currentState.isMenuOpen    = false;

    _aso_edn8_menu_top_left     = {-1, -1};
    _aso_edn8_menu_top_right    = {-1, -1};
    _aso_edn8_menu_bottom_left  = {-1, -1};
    _aso_edn8_menu_bottom_right = {-1, -1};
}

/**
 *
 */
void EverDriveN8Analyzer::analyze(Point position, const unsigned char *color)
{
    if (color[0] > 32 && color[1] > 32 && color[2] > 32)
    {
        if (_aso_edn8_menu_top_left.x == -1)
        {
            _aso_edn8_menu_top_left = position;
            _aso_edn8_menu_bottom_left.x = position.x;
        }
    }
    else
    {
        if (_aso_edn8_menu_top_left.x != -1 && _aso_edn8_menu_top_right.x == -1)
        {
            _aso_edn8_menu_top_right = position;
            _aso_edn8_menu_bottom_right.x = position.x;
        }
        else if (_aso_edn8_menu_top_right.x != -1)
        {
            if (_aso_edn8_menu_bottom_left.y == -1 && position.x == _aso_edn8_menu_bottom_left.x)
            {
                _aso_edn8_menu_bottom_left.y = position.y;
                _aso_edn8_menu_bottom_right.y = position.y;
            }
        }
    }
}

/**
 *
 */
void EverDriveN8Analyzer::conclude()
{
    _currentState.isMenuOpen = (
        aso::isBetween(_aso_edn8_menu_top_left.x,     715 - 20,  715 + 20) &&
        aso::isBetween(_aso_edn8_menu_top_left.y,     275 - 20,  275 + 20) &&
        aso::isBetween(_aso_edn8_menu_top_right.x,    1185 - 20, 1185 + 20) &&
        aso::isBetween(_aso_edn8_menu_top_right.y,    275 - 20,  275 + 20) &&
        aso::isBetween(_aso_edn8_menu_bottom_left.x,  715 - 20,  715 + 20) &&
        aso::isBetween(_aso_edn8_menu_bottom_left.y,  745 - 20,  745 + 20) &&
        aso::isBetween(_aso_edn8_menu_bottom_right.x, 1185 - 20, 1185 + 20) &&
        aso::isBetween(_aso_edn8_menu_bottom_right.y, 745 - 20,  745 + 20)
    );
}

/**
 *
 */
void EverDriveN8Analyzer::dispatch()
{
    if (_currentState.isMenuOpen)
    {
        if (!_previousState.isMenuOpen)
        {
            _events.push(EverDriveN8Event::MENU_OPEN);
        }
    }
    else if (_previousState.isMenuOpen)
    {
        _events.push(EverDriveN8Event::MENU_CLOSE);
    }
}

/**
 *
 */
EverDriveN8State EverDriveN8Analyzer::state() const
{
    return _currentState;
}

}
