#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class GUINode : public sf::Drawable, public sf::Transformable {
private:
    std::vector<std::unique_ptr<GUINode>> _children;
    bool is_visible, is_active, is_focused;
    size_t id;

public:
    void attachChild(std::unique_ptr<GUINode> node);
    std::unique_ptr<GUINode> detachChild(const GUINode& node);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time dt);
    void event(sf::Event evnt);
    
    virtual void onDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void onUpdate(sf::Time dt);
    virtual void onEvent(sf::Event evnt);

    void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateChildren(sf::Time dt);
    void eventChildren(sf::Event evnt);
};