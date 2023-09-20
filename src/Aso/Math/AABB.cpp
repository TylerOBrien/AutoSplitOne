/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Math/AABB.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso
{

/**
 *
 */
AABB::AABB()
{}

/**
 *
 */
AABB::AABB(Point position, Rect dimensions)
    : Point(position),
      Rect(dimensions)
{}

/**
 *
 */
AABB::AABB(int x, int y, int w, int h)
    : Point(x, y),
      Rect(w, h)
{}

/**
 *
 */
int AABB::xMin() const
{
    return x;
}

/**
 *
 */
int AABB::xMax() const
{
    return x + w;
}

/**
 *
 */
int AABB::yMin() const
{
    return y;
}

/**
 *
 */
int AABB::yMax() const
{
    return y + h;
}

/**
 *
 */
bool AABB::contains(AABB bounds) const
{
    return xMin() <= bounds.xMax() &&
           xMax() >= bounds.xMin() &&
           yMin() <= bounds.yMax() &&
           yMax() >= bounds.yMin();
}

/**
 *
 */
bool AABB::contains(Point position) const
{
    return xMin() <= position.x &&
           xMax() >= position.x &&
           yMin() <= position.y &&
           yMin() >= position.y;
}

}
