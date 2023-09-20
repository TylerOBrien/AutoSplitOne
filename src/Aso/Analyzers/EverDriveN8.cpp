/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Analyzers/EverDriveN8.hpp>
#include <Aso/Math/Point.hpp>

/*
|--------------------------------------------------------------------------
| Config
|--------------------------------------------------------------------------
*/

enum EverDriveN8Config {
    MENU_X      = 475,
    MENU_Y      = 13,
    MENU_W      = 1324,
    MENU_H      = 1054,
    MENU_XMAX   = MENU_X + MENU_W,
    MENU_YMAX   = MENU_Y + MENU_H,
    MENU_PIXELS = MENU_W * MENU_H,
};

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

uint8_t  _aso_everdrive_n8_menu_average_r = 0;
uint8_t  _aso_everdrive_n8_menu_average_g = 0;
uint8_t  _aso_everdrive_n8_menu_average_b = 0;
uint32_t _aso_everdrive_n8_menu_sum_r     = 0;
uint32_t _aso_everdrive_n8_menu_sum_g     = 0;
uint32_t _aso_everdrive_n8_menu_sum_b     = 0;

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
    _previousState           = _currentState;
    _currentState.isMenuOpen = false;

    _aso_everdrive_n8_menu_average_r = 0;
    _aso_everdrive_n8_menu_average_g = 0;
    _aso_everdrive_n8_menu_average_b = 0;
    _aso_everdrive_n8_menu_sum_r     = 0;
    _aso_everdrive_n8_menu_sum_g     = 0;
    _aso_everdrive_n8_menu_sum_b     = 0;
}

/**
 *
 */
void EverDriveN8Analyzer::analyze(Point position, const unsigned char *color)
{
    if (position.x >= EverDriveN8Config::MENU_X &&
        position.x <= EverDriveN8Config::MENU_XMAX &&
        position.y >= EverDriveN8Config::MENU_Y &&
        position.y <= EverDriveN8Config::MENU_YMAX)
    {
        _aso_everdrive_n8_menu_sum_r += color[2];
        _aso_everdrive_n8_menu_sum_g += color[1];
        _aso_everdrive_n8_menu_sum_b += color[0];
    }
}

/**
 *
 */
void EverDriveN8Analyzer::conclude()
{
    _aso_everdrive_n8_menu_average_r = _aso_everdrive_n8_menu_sum_r / EverDriveN8Config::MENU_PIXELS;
    _aso_everdrive_n8_menu_average_g = _aso_everdrive_n8_menu_sum_g / EverDriveN8Config::MENU_PIXELS;
    _aso_everdrive_n8_menu_average_b = _aso_everdrive_n8_menu_sum_b / EverDriveN8Config::MENU_PIXELS;

    _currentState.isMenuOpen = (
        _aso_everdrive_n8_menu_average_r > 24 &&
        _aso_everdrive_n8_menu_average_r < 48 &&
        _aso_everdrive_n8_menu_average_g > 24 &&
        _aso_everdrive_n8_menu_average_g < 48 &&
        _aso_everdrive_n8_menu_average_b > 24 &&
        _aso_everdrive_n8_menu_average_b < 48
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
