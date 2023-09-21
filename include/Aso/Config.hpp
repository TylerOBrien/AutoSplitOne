#ifndef _ASO_CONFIG_HPP_
#define _ASO_CONFIG_HPP_

#include <Aso/Aso.hpp>

namespace aso {

enum Config {
    GAME_X = 260,
    GAME_Y = 0,
    GAME_W = 1400,
    GAME_H = 1080,
    GAME_XMAX = Config::GAME_X + Config::GAME_W,
    GAME_YMAX = Config::GAME_Y + Config::GAME_H,
};

}

#endif
