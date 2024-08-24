#pragma once

#include "State.h"
#include "SceneNode.h"
#include "Human.h"
#include "InputManager.h"

class Game : public State {
public:
    enum class Layer : size_t {
        Floor,
        Air,
        Count
    };

private:
    sf::View _view;
    Manager::Game::Texture _textures;
    SceneNode _scene;
    std::array<SceneNode*, (size_t)Layer::Count> _layers;
    Human* _player;
    InputManager _input_manager;

    void buildGame();
    void loadFonts();
    void loadTextures();

public:
    Game(State::Context context, StateStack& stack) : State(context, stack)  {
        loadFonts();
        loadTextures();
        buildGame();
    }

    bool evaluateEvent(const sf::Event& evnt) override;
    bool handleRealtime() override;
    bool update(sf::Time dt) override;
    bool draw() const override;
};