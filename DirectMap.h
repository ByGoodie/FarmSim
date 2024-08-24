#pragma once

#include <SFML/Graphics.hpp>
#include <array>

template<typename Resource, typename ID>
class DirectMap {
private:
    std::array<Resource, (size_t)ID::Count> _resources;

public:
    DirectMap();

    Resource& get(ID id);
    Resource& operator[](ID id);
};

#include "DirectMap.inl"