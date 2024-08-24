#include "SceneNode.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include "Command.h"

unsigned int SceneNode::getCategory() const {
    return (unsigned int)Category::Node;
}

void SceneNode::setParent(SceneNode* node) {
    _parent = node;
}

SceneNode* SceneNode::getParent() {
    return _parent;
}

void SceneNode::attachChild(std::unique_ptr<SceneNode> node) {
    node->setParent(this);
    _children.push_back(std::move(node));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(
        _children.begin(),
        _children.end(),
        [&] (const std::unique_ptr<SceneNode>& e) {
            return &node == e.get();
        }
    );

    assert(found != _children.end());

    std::unique_ptr<SceneNode> f_node = std::move(*found);

    _children.erase(found);

    return std::move(f_node);
}

sf::Transform SceneNode::getGlobalTransform() {
	sf::Transform result = this->getTransform();

	if (_parent != nullptr) {
		result *= _parent->getGlobalTransform();
	}

	return result;
}

sf::Vector2f SceneNode::getGlobalPosition() {
    sf::Vector2f result = this->getPosition();

    if (_parent != nullptr) {
        result += _parent->getGlobalPosition();
    }

	return result;
}

void SceneNode::update(sf::Time dt) {
	this->onUpdate(dt);

	updateChildren(dt);	
}

void SceneNode::updateChildren(sf::Time dt) {
	for (auto& node : _children) {
		node->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= this->getTransform();
    //std::cout << "SN Drw" << std::endl;
	this->onDraw(target, states);

	this->drawChildren(target, states);
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& node : _children) {
        node->draw(target, states);
    }
}

void SceneNode::onCommand(Command cmd) {
    if (this->getCategory() & cmd.category) {
        cmd.action(*this);
    }
}

void SceneNode::distributeCommandChildren(Command cmd) {
    for (auto& node : _children) {
        node->distributeCommand(cmd);
    }
}

void SceneNode::distributeCommand(Command cmd) {
    this->onCommand(cmd);

    this->distributeCommandChildren(cmd);
}


void SceneNode::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {}
void SceneNode::onUpdate(sf::Time dt) {}