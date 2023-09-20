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

#ifndef _ASO_APP_HPP_
#define _ASO_APP_HPP_

#include <Aso/Event.hpp>

#include <queue>

namespace aso {

enum AppEvent {
    KEY_PRESS = 0x00000008
};

class App {
protected:
    bool _isAlive;
    bool _isConnectedToLiveSplit;
    std::queue<Event> _events;
public:
    App();

    bool isAlive();
    bool isConnectedToLiveSplit();

    void run();
    void connect();
    void disconnect();
    void update();
    void sleep();

    Event poll();
};

}

#endif
