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

#ifndef _ASO_GRAPHICS_STB_PNG_FILE_HPP_
#define _ASO_GRAPHICS_STB_PNG_FILE_HPP_

#include <Aso/Math/Rect.hpp>

#include <stb/stb_image.h>
#include <string>

namespace aso {

class StbPngFile
    : public Rect {
protected:
    int _nchannels;
    stbi_uc *_data;
public:
    StbPngFile(const std::string &filepath);
    ~StbPngFile();

    int nchannels() const;
    const stbi_uc* data() const;
};

}

#endif
