/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Graphics/Color.hpp>
#include <Aso/Math/Math.hpp>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
Color::Color()
    : r(0),
      g(0),
      b(0),
      a(255)
{}

/**
 *
 */
Color::Color(BGR bgr)
    : r(bgr.r),
      g(bgr.g),
      b(bgr.b),
      a(255)
{}

/**
 *
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b)
    : r(r),
      g(g),
      b(b),
      a(255)
{}

/**
 *
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    : r(r),
      g(g),
      b(b),
      a(a)
{}

/**
 *
 */
Color Color::diff(Color color) const
{
    return Color(
        aso::diff(r, color.r),
        aso::diff(g, color.g),
        aso::diff(b, color.b),
        aso::diff(a, color.a)
    );
}

/**
 *
 */
int Color::compare(Color color, Color tolerance) const
{
   return compare(color, tolerance, Color(1, 1, 1, 1));
}

/**
 *
 */
int Color::compare(Color color, Color tolerance, Color weight) const
{
    int score = 0;
    Color difference = diff(color);

    if (difference.r <= tolerance.r) {
        score += weight.r;
    }

    if (difference.g <= tolerance.g) {
        score += weight.g;
    }

    if (difference.b <= tolerance.b) {
        score += weight.b;
    }

    if (difference.a <= tolerance.a) {
        score += weight.a;
    }

    return score;
}

/**
 *
 */
bool Color::tolerates(Color color, Color tolerance) const
{
    Color difference = diff(color);

    return (
        difference.r <= tolerance.r &&
        difference.g <= tolerance.g &&
        difference.b <= tolerance.b &&
        difference.a <= tolerance.a
    );
}

}
