#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Command.h"

class InputManager {
public:
    enum class Action : size_t {
        MoveRight,
        MoveLeft,
        MoveUp,
        MoveDown,
        Count
    };

private:
    std::unordered_map<sf::Keyboard::Key, Action> _key_bindings;
    std::unordered_map<Action, Command> _act_bindings;

public:
    InputManager();

    Command evaluateEvent(const sf::Event& evnt);
    Command evaluateRealtime(Action action);
};