#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <memory>
#include "ResourceEnums.h"

class StateStack;

class State {
public:
    struct Context {
        Context(sf::RenderWindow& window, Manager::Common::Font& fonts, Manager::Common::Texture& textures) : window(window), fonts(fonts), textures(textures) {}

        sf::RenderWindow& window;
        Manager::Common::Font& fonts;
        Manager::Common::Texture& textures;
    };

private:
    Context _context;
    StateStack& _stack;

public:
    State(Context context, StateStack& stack) : _context(context), _stack(stack) {}

    virtual bool evaluateEvent(const sf::Event& evnt) = 0;
    virtual bool handleRealtime() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool draw() const = 0;

    const Context& getContext() const;

    void pushState(State* state);
    void removeState();
    void removeAllStates();
};