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

#ifndef _ASO_MATH_MATH_HPP_
#define _ASO_MATH_MATH_HPP_

#include <Aso/Aso.hpp>

#include <random>

namespace aso {

template <class NumberTy>
inline NumberTy diff(NumberTy a, NumberTy b)
{
   return (a > b) ? (a - b) : (b - a);
}

template <class NumberTy>
inline bool isBetween(NumberTy value, NumberTy min, NumberTy max)
{
   return a >= min && a <= max;
}

inline int random(int min, int max)
{
   return min + std::rand() % ((max + 1) - min);
}

}

#endif
