#include "GUINode.h"
#include <algorithm>

void GUINode::attachChild(std::unique_ptr<GUINode> node) {
    _children.push_back(std::move(node));
}

std::unique_ptr<GUINode> GUINode::detachChild(const GUINode& node) {
    auto found = std::find_if(
        _children.begin(),
        _children.end(),
        [&](const std::unique_ptr<GUINode>& i) {
            return i.get() == &node;
        }
    );

    if (found == _children.end()) return nullptr;

    auto result = std::move(*found);

    _children.erase(found);

    return std::move(result);
}

void GUINode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    this->onDraw(target, states);

    this->drawChildren(target, states);
}

void GUINode::update(sf::Time dt) {
    this->onUpdate(dt);

    this->updateChildren(dt);
}

void GUINode::event(sf::Event evnt) {
    this->onEvent(evnt);
    
    this->eventChildren(evnt);
}

void 