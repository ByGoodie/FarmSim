#include "Animator.h"

template <typename ID>
Animator<ID>::Animator(DirectMap<Animation, ID>& animations, ID default_anim) : _animations(animations), _default_anim((size_t)default_anim), _current_anim((size_t)default_anim) {}

template <typename ID>
void Animator<ID>::setDefaultAnim(ID default_anim) {
    _default_anim = (size_t)default_anim;
}

template <typename ID>
bool Animator<ID>::nextFrame() {
    if (getAnimation().nextFrame()) {
        setAnimation((ID)_default_anim);
        return true;
    }

    return false;
}

template <typename ID>
void Animator<ID>::setAnimation(ID anim) {
    _current_anim = (size_t)anim;
    getAnimation().reset();
}

template <typename ID>
ID Animator<ID>:: getAnimID() const {
    return (ID)_current_anim;
}

template <typename ID>
Animation& Animator<ID>::getAnimation() const {
    return _animations[(ID)_current_anim];
}