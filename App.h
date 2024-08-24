#pragma once

#include "State.h"
#include "StateStack.h"
#include "ResourceEnums.h"
#include "DirectMap.h"

class App {
public:
    typedef DirectMap<sf::Texture, FarmSim::Texture::Common> TextureManager;
    typedef DirectMap<sf::Font, FarmSim::Font::Common> FontManager;

private:
    StateStack _state_stack;
    State::Context _context;
    FontManager _fonts;
    TextureManager _textures;
    sf::RenderWindow _window;
    sf::Clock _clock;
    sf::Time _dt;
    sf::Event _event;
    sf::Sprite _logo;

    void loadFonts();
    void loadTextures();

public:
    App();

    void responseEvent();
    void update(sf::Time dt);
    void draw() const;
    void run();
};