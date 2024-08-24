#pragma once

#include <functional>
#include <iostream>

class SceneNode;

struct Command {
    unsigned int category;
    std::function<void(SceneNode&)> action;
};

template <typename T>
std::function<void(SceneNode&)> convertFn(std::function<void(T&)> fn) {
    return [=] (SceneNode& node) {
        T& obj = dynamic_cast<T&>(node);
        fn(obj);
    };
}