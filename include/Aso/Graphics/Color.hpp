/*
 * Copyright (C) 2021-2023  Tyler O'Brien <hello@tylerobrien.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef _ASO_GRAPHICS_COLOR_HPP_
#define _ASO_GRAPHICS_COLOR_HPP_

#include <Aso/Aso.hpp>

namespace aso {

struct BGR {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

class Color {
public:
    enum {
        RED, GREEN, BLUE, ALPHA
    };

    uint8_t r, g, b, a;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    Color diff(Color color) const;

    int compare(Color color, Color tolerance) const;
    int compare(Color color, Color tolerance, Color weight) const;

    bool tolerates(Color color, Color tolerance) const;
};

}

#endif
