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

#include <Aso/Graphics/StbPngFile.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/*
|--------------------------------------------------------------------------
| Functions
|--------------------------------------------------------------------------
*/

namespace aso {

/**
 *
 */
inline stbi_uc* _aso_stbi_load(int *width, int *height, int *nchannels, const std::string &filepath)
{
    int _width     = 0;
    int _height    = 0;
    int _nchannels = 0;
    stbi_uc *data  = stbi_load(filepath.c_str(), &_width, &_height, &_nchannels, 4);

    *width     = _width;
    *height    = _height;
    *nchannels = _nchannels;

    return data;
}

/**
 *
 */
StbPngFile::StbPngFile(const std::string &filepath)
    : _data(_aso_stbi_load(&w, &h, &_nchannels, filepath))
{}

/**
 *
 */
StbPngFile::~StbPngFile()
{
    stbi_image_free(_data);
}

/**
 *
 */
int StbPngFile::nchannels() const
{
    _nchannels;
}

/**
 *
 */
const stbi_uc* StbPngFile::data() const
{
    stbi_image_free(_data);
}

}
