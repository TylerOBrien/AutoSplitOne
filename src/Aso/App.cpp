/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/App.hpp>
#include <Aso/IO/LiveSplitOneServer.hpp>

#include <chrono>
#include <curses.h>
#include <csignal>
#include <sys/ioctl.h>
#include <thread>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

bool _aso_app_alive = 1;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
void _aso_app_quit(int sig)
{
    endwin();
    exit(0);
}

/**
 *
 */
App::App()
    : _isAlive(true),
      _isConnectedToLiveSplit(false)
{
    signal(SIGINT, _aso_app_quit);
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
}

/**
 *
 */
void App::run()
{
    LiveSplitOneServer::run(
        std::bind(&App::connect, this),
        std::bind(&App::disconnect, this),
        std::bind(&App::update, this)
    );
}

/**
 *
 */
void App::connect()
{
    _isConnectedToLiveSplit = true;
}

/**
 *
 */
void App::disconnect()
{
    _isConnectedToLiveSplit = false;
}

/**
 *
 */
void App::update()
{
    static char ch;

    if ((ch = getch()) != ERR)
    {
        _events.push(Event(AppEvent::KEY_PRESS, ch));
    }

    sleep();
}

/**
 *
 */
void App::sleep()
{
    std::this_thread::sleep_for(
        std::chrono::nanoseconds(4000000)
    );
}

/**
 *
 */
bool App::isAlive()
{
    return _isAlive;
}

/**
 *
 */
bool App::isReady()
{
    return true;
}

}
