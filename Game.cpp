#include "Game.h"
#include <iostream>

void Game::loadFonts() {}
void Game::loadTextures() {
    _textures[FarmSim::Texture::Game::Girl].loadFromFile("Resources/Textures/Girl.png");
}

void Game::buildGame() {
    std::unique_ptr<SceneNode> _player_n(new Human(Human::ID::Player, _textures)), _npc(new Human(Human::ID::NPC, _textures));
    _player = static_cast<Human*>(_player_n.get());

    std::unique_ptr<SceneNode> floor(new SceneNode()), air(new SceneNode());

    _layers[(size_t)Layer::Air] = air.get();
    _layers[(size_t)Layer::Floor] = floor.get();
    _layers[(size_t)Layer::Floor]->attachChild(std::move(_player_n));
    _layers[(size_t)Layer::Floor]->attachChild(std::move(_npc));

    _scene.attachChild(std::move(floor));
    _scene.attachChild(std::move(air));

    _view.setCenter(_player->getPosition());

    _view.setSize((sf::Vector2f)this->getContext().window.getSize());
    this->getContext().window.setView(_view);

    //std::cout << "Txtr Addr: " << &_textures[(size_t)FarmSim::Texture::Game::Girl] << std::endl;
    //std::cout << "Wnd Addr: " << &this->getContext().window << std::endl;
}

bool Game::handleRealtime() {
    for (size_t i = 0; i < (size_t)InputManager::Action::Count; i++) {
        Command cmd = _input_manager.evaluateRealtime((InputManager::Action)i);

        if (cmd.category != 0) _scene.distributeCommand(cmd);
    }

    return false;
}

bool Game::evaluateEvent(const sf::Event& evnt) {
    Command cmd = _input_manager.evaluateEvent(evnt);

    if (cmd.category != 0) _scene.distributeCommand(cmd);

    return false;
}

bool Game::update(sf::Time dt) {
    _scene.update(dt);
    _view.setCenter(_player->getPosition());
    this->getContext().window.setView(_view);
    _player->setVelocity(sf::Vector2f(0.f, 0.f));
    return false;
}

bool Game::draw() const {
    this->getContext().window.setView(_view);
    _scene.draw(this->getContext().window, sf::RenderStates::Default);
    return false;
}