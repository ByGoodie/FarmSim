#pragma once

#include "DirectMap.h"
#include <SFML/Graphics.hpp>

namespace FarmSim {
    namespace Texture {
        enum class Common : size_t {
            Logo,
            Count
        };
        enum class Game : size_t {
            Girl,
            MapTiles,
            Count
        };
    }

    namespace Font {
        enum class Common : size_t {
            Arrial,
            Count
        };
    }
}

namespace Manager {
    namespace Common {
        typedef DirectMap<sf::Texture, FarmSim::Texture::Common> Texture;
        typedef DirectMap<sf::Font, FarmSim::Font::Common> Font;
    }

    namespace Game {
        typedef DirectMap<sf::Texture, FarmSim::Texture::Game> Texture;
        //typedef DirectMap<sf::Font, FarmSim::Font::Game> FontManager;
    }
}