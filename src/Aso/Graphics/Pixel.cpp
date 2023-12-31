/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Graphics/Pixel.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
Pixel::Pixel()
{}

/**
 *
 */
Pixel::Pixel(Point position, Color color)
    : Point(position),
      Color(color)
{}

}
