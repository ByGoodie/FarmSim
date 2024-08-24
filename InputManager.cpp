#include "InputManager.h"
#include "Human.h"
#include "Categories.h"
#include <cassert>
#include <iostream>

static void playerMove(Human& human, sf::Vector2f d) {
    human.accelerate(d);
    if (human.getAnimator().getAnimID() == Human::Animations::Walk) return;
    human.getAnimator().setDefaultAnim(Human::Animations::Walk);
    human.getAnimator().setAnimation(Human::Animations::Walk);
}

static void playerStop(Human& human) {
    human.getAnimator().setDefaultAnim(Human::Animations::Idle);
    human.getAnimator().setAnimation(Human::Animations::Idle);
}

InputManager::InputManager() {
    _key_bindings[sf::Keyboard::Key::A] = Action::MoveLeft;
    _key_bindings[sf::Keyboard::Key::D] = Action::MoveRight;
    _key_bindings[sf::Keyboard::Key::W] = Action::MoveUp;
    _key_bindings[sf::Keyboard::Key::S] = Action::MoveDown;

    std::function<void(Human&)> moveLeft = std::bind(playerMove, std::placeholders::_1, sf::Vector2f(-50.f, 0.f));
    std::function<void(Human&)> moveRight = std::bind(playerMove, std::placeholders::_1, sf::Vector2f(50.f, 0.f));
    std::function<void(Human&)> moveUp = std::bind(playerMove, std::placeholders::_1, sf::Vector2f(0.f, -50.f));
    std::function<void(Human&)> moveDown = std::bind(playerMove, std::placeholders::_1, sf::Vector2f(0.f, 50.f));


    _act_bindings[Action::MoveLeft] = {(unsigned int)Category::Player, convertFn<Human>(moveLeft)};
    _act_bindings[Action::MoveRight] = {(unsigned int)Category::Player, convertFn<Human>(moveRight)};
    _act_bindings[Action::MoveUp] = {(unsigned int)Category::Player, convertFn<Human>(moveUp)};
    _act_bindings[Action::MoveDown] = {(unsigned int)Category::Player, convertFn<Human>(moveDown)};
}

Command InputManager::evaluateEvent(const sf::Event& evnt) {
    if (evnt.type == sf::Event::KeyPressed) {
        auto found = _key_bindings.find(evnt.key.code);

        if (found == _key_bindings.end()) return {0};
        return _act_bindings.find(found->second)->second;
    }
    else if (evnt.type == sf::Event::KeyReleased) {
        if (evnt.key.code == sf::Keyboard::Key::A || evnt.key.code == sf::Keyboard::Key::D || evnt.key.code == sf::Keyboard::Key::W || evnt.key.code == sf::Keyboard::Key::S)
            return {(unsigned int)Category::Player, convertFn<Human>(playerStop)};
    }

    return {0};
}

Command InputManager::evaluateRealtime(Action action) {
    auto found = std::find_if(_key_bindings.begin(), _key_bindings.end(),
    [&](const std::pair<sf::Keyboard::Key, Action>& x) {
        return x.second == action;
    });

    if (found == _key_bindings.end()) assert(0);
    
    if (sf::Keyboard::isKeyPressed(found->first)) return _act_bindings[action];
    return {0};
}