/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Event.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
Event::Event()
    : type(0), data(0)
{}

/**
 *
 */
Event::Event(int type)
    : type(type), data(0)
{}

/**
 *
 */
Event::Event(int type, int data)
    : type(type), data(data)
{}

/**
 *
 */
Event::operator bool () const
{
    return (bool) type;
}

}
