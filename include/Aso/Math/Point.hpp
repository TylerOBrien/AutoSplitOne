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

#ifndef _ASO_MATH_POINT_HPP_
#define _ASO_MATH_POINT_HPP_

#include <Aso/Aso.hpp>

namespace aso {

class Point {
public:
    enum {
        X, Y
    };

    int x, y;

    Point();
    Point(int x, int y);

    Point operator + (Point position) const;
    Point operator - (Point position) const;

    bool isBetween(Point min, Point max) const;
};

}

#endif
