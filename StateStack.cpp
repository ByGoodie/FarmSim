#include "StateStack.h"
#include "State.h"
#include <iostream>

void StateStack::pushState(State* state) {
    _pending_changes.push({Action::Push, std::unique_ptr<State>(state)});
}

void StateStack::removeState() {
    _pending_changes.push({Action::Remove, 0});
}

void StateStack::removeAllStates() {
    _pending_changes.push({Action::RemoveAll, 0});
}

void StateStack::evaluateEvent(const sf::Event& evnt) {
    for (auto i = _states.rbegin(); i != _states.rend(); i++) {
        State* state = i->get();
        if (!state->evaluateEvent(evnt)) break;
    }

    this->executePendingChanges();
}

void StateStack::handleRealtime() {
    for (auto i = _states.rbegin(); i != _states.rend(); i++) {
        State* state = i->get();
        if (!state->handleRealtime()) break;
    }

    this->executePendingChanges();
}

void StateStack::update(sf::Time dt) {
    for (auto i = _states.rbegin(); i != _states.rend(); i++) {
        State* state = i->get();
        if (!state->update(dt)) break;
    }

    this->executePendingChanges();
}

void StateStack::draw() const {
    for (auto i = _states.begin(); i != _states.end(); i++) {
        //std::cout << "Dbg 11" << std::endl;
        State* state = i->get();
        if (!state->draw()) break;
        //std::cout << "Dbg 12" << std::endl;
    }
    //std::cout << "Dbg 13" << std::endl;
}

void StateStack::executePendingChanges() {
    while (!_pending_changes.empty()) {
        PendingChange& change = _pending_changes.front();

        if (change.action == Action::Push) {
            _states.push_back(std::move(change.state));
        }
        else if (change.action == Action::Remove) {
            _states.pop_back();
        }
        else if (change.action == Action::RemoveAll) {
            _states.clear();
        }

        _pending_changes.pop();
    }
}