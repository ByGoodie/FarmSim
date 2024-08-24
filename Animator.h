#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "Animation.h"
#include "DirectMap.h"

enum class SheetStyle : size_t {
    Row = 1,
    Column = 2,
    Composite = 4
};

template <typename ID>
class Animator {
private:
    DirectMap<Animation, ID>& _animations;
    size_t _default_anim, _current_anim;

public:
    Animator(DirectMap<Animation, ID>& animations, ID default_anim);

    void setDefaultAnim(ID default_anim);

    bool nextFrame();
    void setAnimation(ID anim);

    ID getAnimID() const;
    Animation& getAnimation() const;
};

#include "Animator.inl"