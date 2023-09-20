/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Math/Point.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
Point::Point()
    : x(0),
      y(0)
{}

/**
 *
 */
Point::Point(int x, int y)
    : x(x),
      y(y)
{}

/**
 *
 */
Point Point::operator + (Point position) const
{
    return Point(x + position.x, y + position.y);
}

/**
 *
 */
Point Point::operator - (Point position) const
{
    return Point(x - position.x, y - position.y);
}

/**
 *
 */
bool Point::isBetween(Point min, Point max) const
{
    return x >= min.x &&
           x <= max.x &&
           y >= min.y &&
           y <= max.y;
}

}
