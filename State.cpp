#include "State.h"
#include "StateStack.h"

const State::Context& State::getContext() const {
    return _context;
}

void State::pushState(State* state) {
    _stack.pushState(state);
}

void State::removeState() {
    _stack.removeState();
}

void State::removeAllStates() {
    _stack.removeAllStates();
}