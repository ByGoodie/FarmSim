#include "App.h"
#include "Game.h"
#include <iostream>

const sf::Time _frame_tm = sf::seconds(1.f / 60.f);

App::App() : _window(sf::VideoMode::getFullscreenModes()[0], "Farm Sim"), _context(_window, _fonts, _textures), _dt(sf::seconds(0.f)) {
    loadFonts();
    loadTextures();
    _state_stack.pushState(new Game(_context, _state_stack));
    _window.setKeyRepeatEnabled(false);
    _logo.setTexture(_context.textures[FarmSim::Texture::Common::Logo]);
    //std::cout << "Wnd Addr: " << &_window << std::endl;
}

void App::responseEvent() {
    if (_event.type == sf::Event::Closed) {
        _window.close();
    }
    else {
        _state_stack.evaluateEvent(_event);
    }
}

void App::update(sf::Time dt) {
    _state_stack.update(dt);
}

void App::draw() const {
    _state_stack.draw();
}

void App::run() {
    while (_window.isOpen()) {
        _dt += _clock.restart();
        //std::cout << "Dbg 1" << std::endl;
        while (_dt >= _frame_tm) {
            _dt -= _frame_tm;
            _state_stack.handleRealtime();
            _state_stack.update(_frame_tm);
        }
        //std::cout << "Dbg 2" << std::endl;
        _window.clear(sf::Color::Black);
        _state_stack.draw();
        _window.setView(_window.getDefaultView());
        _window.draw(_logo);
        //std::cout << "Dbg 3" << std::endl;
        _window.display();
        while (_window.pollEvent(_event)) {
            responseEvent();
        }
    }
}

void App::loadFonts() {
    _fonts[FarmSim::Font::Common::Arrial].loadFromFile("Resources/Fonts/Arial.ttf");
}

void App::loadTextures() {
    _textures[FarmSim::Texture::Common::Logo].loadFromFile("Resources/Textures/Logo.png");
}