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

#ifndef _ASO_ANALYZER_NES_N8_HPP_
#define _ASO_ANALYZER_NES_N8_HPP_

#include <Aso/Analyzers/Base.hpp>
#include <Aso/OpenCV2.hpp>

#include <queue>

namespace aso {

struct EverDriveN8State {
    bool isMenuOpen;
};

enum EverDriveN8Event {
    MENU_OPEN  = 0x00000005,
    MENU_CLOSE = 0x00000006,
};

class EverDriveN8Analyzer
    : public BaseAnalyzer {
protected:
    EverDriveN8State _currentState;
    EverDriveN8State _previousState;
    std::queue<EverDriveN8Event> _events;
public:
    static int index;

    typedef EverDriveN8Event EventType;
    typedef EverDriveN8State StateType;

    EverDriveN8Analyzer();

    Event poll();

    void reset();
    void analyze(Point position, int index, const unsigned char *color);
    void conclude();
    void dispatch();

    EverDriveN8State state() const;
};

}

#endif
