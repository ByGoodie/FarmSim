#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>
#include <memory>
#include <queue>

class State;

class StateStack {
public:
    enum class Action {
        Push,
        Remove,
        RemoveAll
    };

    struct PendingChange {
        Action action;
        std::unique_ptr<State> state;
    };

private:
    std::vector<std::unique_ptr<State>> _states;
    std::queue<PendingChange> _pending_changes;

    void executePendingChanges();

public:
    void pushState(State* state);
    void removeState();
    void removeAllStates();

    void evaluateEvent(const sf::Event& evnt);
    void handleRealtime();
    void update(sf::Time dt);
    void draw() const;
};