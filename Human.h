#pragma once

#include "Entity.h"
#include "ResourceEnums.h"
#include "Animator.h"

class Human : public Entity {
public:
    enum class ID : size_t {
        Player,
        NPC
    };

    enum class Animations : size_t {
        Idle,
        Walk,
        Count
    };

    typedef Animator<Animations> Animator;

private:
    sf::Sprite _sprite;
    Animator _animator;
    DirectMap<Animation, Animations> _animations;

    ID _id;

    FarmSim::Texture::Game toTexture(ID id) const;

public:
    explicit Human(ID id, Manager::Game::Texture& textures);

    unsigned int getCategory() const override;
    Animator& getAnimator();

    void onUpdate(sf::Time dt) override;
    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
};