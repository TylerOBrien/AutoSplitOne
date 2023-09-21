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

#ifndef _ASO_ANALYZER_SCREEN_HPP_
#define _ASO_ANALYZER_SCREEN_HPP_

#include <Aso/Analyzers/Base.hpp>

#include <queue>

namespace aso {

struct ScreenState {
    bool isBlack;
    bool isWhite;
};

enum ScreenEvent {
    BLACK   = 0x00000001,
    UNBLACK = 0x00000002,
    WHITE   = 0x00000003,
    UNWHITE = 0x00000004,
};

class ScreenAnalyzer
    : public BaseAnalyzer {
protected:
    ScreenState _currentState;
    ScreenState _previousState;
    std::queue<ScreenEvent> _events;
public:
    static int index;

    typedef ScreenEvent EventType;
    typedef ScreenState StateType;

    ScreenAnalyzer();

    Event poll();

    void reset();
    void analyze(Point position, const unsigned char *color);
    void conclude();
    void dispatch();

    ScreenState state() const;
};

}

#endif
