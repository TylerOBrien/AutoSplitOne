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

/*
|--------------------------------------------------------------------------
| Includes
|--------------------------------------------------------------------------
*/

#include <Aso/Config.hpp>

#include <algorithm>
#include <map>
#include <random>
#include <vector>

/*
|--------------------------------------------------------------------------
| Locals
|--------------------------------------------------------------------------
*/

std::vector<int> _aso_config_uids;
std::map<int, aso::Config::Entry> _aso_config_data;

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {
namespace Config {

/**
 *
 */
inline int _generateId()
{
    return 14039447 + std::rand() % (4268027615 - 14039447);
}

/**
 *
 */
int uid()
{
    int id = _generateId();
    auto begin = _aso_config_uids.begin();
    auto end = _aso_config_uids.end();

    while (std::find(begin, end, id) != end) {
        id = _generateId();
    }

    _aso_config_uids.push_back(id);

    return id;
}

/**
 *
 */
int insert(char value)
{
    int id = uid();
    Entry entry = {0};

    entry.c = value;

    _aso_config_data.insert(std::make_pair(id, entry));

    return id;
}

/**
 *
 */
int insert(int value)
{
    int id = uid();
    Entry entry = {0};

    entry.i = value;

    _aso_config_data.insert(std::make_pair(id, entry));

    return id;
}

/**
 *
 */
int insert(float value)
{
    int id = uid();
    Entry entry = {0};

    entry.f = value;

    _aso_config_data.insert(std::make_pair(id, entry));

    return id;
}

/**
 *
 */
int insert(bool value)
{
    int id = uid();
    Entry entry = {0};

    entry.b = value;

    _aso_config_data.insert(std::make_pair(id, entry));

    return id;
}

/**
 *
 */
int geti(int uid)
{
    return _aso_config_data.find(uid)->second.i;
}

/**
 *
 */
float getf(int uid)
{
    return _aso_config_data.find(uid)->second.f;
}

/**
 *
 */
void set(int uid, char value)
{
    _aso_config_data.find(uid)->second.c = value;
}

/**
 *
 */
void set(int uid, int value)
{
    _aso_config_data.find(uid)->second.i = value;
}

/**
 *
 */
void set(int uid, float value)
{
    _aso_config_data.find(uid)->second.f = value;
}

/**
 *
 */
void set(int uid, bool value)
{
    _aso_config_data.find(uid)->second.b = value;
}

}
}
