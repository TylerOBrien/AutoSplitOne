/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/LiveSplit.hpp>

#include <chrono>
#include <stack>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

std::stack<std::chrono::milliseconds> _aso_ls_splits;
aso::LiveSplit::ServerWriteFunction _aso_ls_write_function = NULL;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso{
namespace LiveSplit {

/**
 *
 */
void connect(ServerWriteFunction write_function)
{
    _aso_ls_write_function = write_function;
}

/**
 *
 */
void disconnect()
{
    _aso_ls_write_function = NULL;
}

/**
 *
 */
void start()
{
    _aso_ls_write_function("start");
    _aso_ls_splits.push(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ));
}

/**
 *
 */
void split()
{
    _aso_ls_write_function("split");
    _aso_ls_splits.push(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ));
}

/**
 *
 */
void undo()
{
    if (!_aso_ls_splits.empty())
    {
        _aso_ls_write_function("undo");
        _aso_ls_splits.pop();
    }
}

/**
 *
 */
void reset()
{
    _aso_ls_write_function("reset");
    _aso_ls_splits = std::stack<std::chrono::milliseconds>();
}

}
}
