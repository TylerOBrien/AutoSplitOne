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

#ifndef _ASO_ANALYZER_BASE_HPP_
#define _ASO_ANALYZER_BASE_HPP_

#include <Aso/Aso.hpp>
#include <Aso/Event.hpp>
#include <Aso/Math/Point.hpp>

namespace aso {

class BaseAnalyzer {
public:
    virtual Event poll() = 0;

    virtual void  reset() = 0;
    virtual void  analyze(Point position, int index, const unsigned char *color) = 0;
    virtual void  conclude() = 0;
    virtual void  dispatch() = 0;
};

}

#endif
