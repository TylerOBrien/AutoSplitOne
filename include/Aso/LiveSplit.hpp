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

#ifndef _ASO_LIVESPLIT_HPP_
#define _ASO_LIVESPLIT_HPP_

#include <Aso/Aso.hpp>

#include <functional>

namespace aso {
namespace LiveSplit {

typedef std::function<void(const char*)> ServerWriteFunction;

void connect(ServerWriteFunction writer);
void disconnect();

void start();
void split();
void reset();
void undo();

}
}

#endif
