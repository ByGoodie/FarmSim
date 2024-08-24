#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Container.h"

class GUI {
private:
    std::vector<std::unique_ptr<Container>> _containers;

public:
    void addContainer(std::unique_ptr<Container> container);
};