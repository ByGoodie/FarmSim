#include "SceneNode.h"

class Entity : public SceneNode {
private:
    sf::Vector2f _velocity;

public:
    sf::Vector2f getVelocity() const;
    void setVelocity(sf::Vector2f velocity);

    void accelerate(sf::Vector2f acceleration);

    virtual void onUpdate(sf::Time dt) override;
};