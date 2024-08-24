#include "Entity.h"

sf::Vector2f Entity::getVelocity() const {
    return _velocity;
}

void Entity::setVelocity(sf::Vector2f velocity) {
    _velocity = velocity;
}

void Entity::accelerate(sf::Vector2f acceleration) {
    _velocity += acceleration;
}

void Entity::onUpdate(sf::Time dt) {
    this->move(this->_velocity * dt.asSeconds());
}