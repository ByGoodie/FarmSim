#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Categories.h"

struct Command;

class SceneNode : public sf::Drawable, public sf::Transformable {
private:
    std::vector<std::unique_ptr<SceneNode>> _children;
    SceneNode* _parent; 

public:
    SceneNode() : _parent(nullptr) {};

    void setParent(SceneNode* node);
    SceneNode* getParent();

    virtual unsigned int getCategory() const;

    void attachChild(std::unique_ptr<SceneNode> node);
    std::unique_ptr<SceneNode> detachChild(const SceneNode& node);

    sf::Transform getGlobalTransform();
    sf::Vector2f getGlobalPosition();

    virtual void onUpdate(sf::Time dt);
    void updateChildren(sf::Time dt);
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onCommand(Command cmd);
    void distributeCommandChildren(Command cmd);

    void distributeCommand(Command cmd);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
};
