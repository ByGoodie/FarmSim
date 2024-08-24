#include "Human.h"
#include <iostream>

Human::Human(ID id,  Manager::Game::Texture& textures) : _id(id), _animator(_animations, Animations::Idle) {
    _animations[Animations::Idle] = Animation(
        sf::Vector2i(16, 16),
        5,
        60,
        sf::IntRect(0, 0, 5, 1),
        textures[this->toTexture(id)],
        nullptr, nullptr
    );

    _animations[Animations::Walk] = Animation(
        sf::Vector2i(16, 16),
        5,
        60,
        sf::IntRect(0, 1, 5, 1),
        textures[this->toTexture(id)],
        nullptr, nullptr
    );

    _sprite.setTexture(_animator.getAnimation().getTexture());
    _sprite.setTextureRect(_animator.getAnimation().getSpriteRect());
    _sprite.setScale(5.f, 5.f);
    _sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
    _sprite.setOrigin(sf::Vector2f(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2));
}

unsigned int Human::getCategory() const {
    switch(_id) {
    case ID::Player:
        return (unsigned int)Category::Player;
    case ID::NPC:
        return (unsigned int)Category::NPC;
    }
}

Human::Animator& Human::getAnimator() {
    return _animator;
}

void Human::onUpdate(sf::Time dt) {
    if (_animator.nextFrame()) _sprite.setTexture(_animator.getAnimation().getTexture());
    _sprite.setTextureRect(_animator.getAnimation().getSpriteRect());
    this->move(this->getVelocity() * dt.asSeconds());
}

void Human::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    //std::cout << "Dbg Hmn 1" << std::endl << "x: " << this->getPosition().x << ", y: " << this->getPosition().y << std::endl;
    //std::cout << "Txtr Addr: " << _sprite.getTexture() << std::endl;
    target.draw(_sprite, states);
    //std::cout << "Dbg Hmn 2" << std::endl;
}

FarmSim::Texture::Game Human::toTexture(ID id) const {
    switch (id) {
        case ID::NPC:
        case ID::Player:
            return FarmSim::Texture::Game::Girl;
    }
}