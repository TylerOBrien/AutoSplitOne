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

#ifndef _ASO_GAME_HPP_
#define _ASO_GAME_HPP_

#include <Aso/Aso.hpp>
#include <Aso/Analyzers/Base.hpp>
#include <Aso/Event.hpp>
#include <Aso/OpenCV2.hpp>

#include <array>
#include <queue>

namespace aso {

class Game {
public:
    static constexpr std::uint8_t MAX_ANALYZERS = 32;
private:
    void __dispatch(Point position, const unsigned char *color);
protected:
    std::array<std::shared_ptr<BaseAnalyzer>, Game::MAX_ANALYZERS> _analyzers;
    std::uint8_t _analyzerCount;
    std::queue<Event> _events;
public:
    Event poll();
    void updateFromCaptureFrame(const cv::Mat &frame);

    template <class Ty>
    inline void add()
    {
        Ty::index = _analyzerCount;
        _analyzers[_analyzerCount] = std::make_shared<Ty>();
        _analyzerCount++;
    }

    template <class Ty>
    inline typename Ty::StateType state() const
    {
        return std::static_pointer_cast<Ty>(_analyzers[Ty::index])->state();
    }
};

}

#endif
