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

#ifndef _ASO_ANALYZER_NINJA_GAIDEN_HPP_
#define _ASO_ANALYZER_NINJA_GAIDEN_HPP_

#include <Aso/Analyzers/Base.hpp>

#include <queue>

namespace aso {

struct NinjaGaidenConfig {
    struct HUD {
        static int xMin();
        static int yMin();
        static int xMax();
        static int yMax();
        static int width();
        static int height();
    };
};

struct NinjaGaidenConfigKey {
    struct HUD {
        static int xMin;
        static int xMax;
        static int yMin;
        static int yMax;
    };
};

struct NinjaGaidenState {
    bool isTimerZero;
};

enum NinjaGaidenEvent {
    TIMER_ZERO = 0x00000009,
};

class NinjaGaidenAnalyzer
    : public BaseAnalyzer {
protected:
    NinjaGaidenState _currentState;
    NinjaGaidenState _previousState;
    std::queue<NinjaGaidenEvent> _events;
public:
    static int index;

    typedef NinjaGaidenState EventType;
    typedef NinjaGaidenState StateType;

    NinjaGaidenAnalyzer();

    Event poll();

    void reset();
    void analyze(Point position, const unsigned char *color);
    void conclude();
    void dispatch();

    bool isWithinHUD(Point position) const;
    bool isWithinKnownZero(Point position) const;
    bool isWithinTimerFirstDigit(Point position) const;
    bool isWithinTimerSecondDigit(Point position) const;
    bool isWithinTimerThirdDigit(Point position) const;

    NinjaGaidenState state() const;
};

}

#endif
