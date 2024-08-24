#include "Grid.h"

template <typename Element>
Grid<Element>::Grid(sf::Vector2i grid_size, sf::Vector2i cell_size) : _grid_size(grid_size), _cell_size(cell_size) {}

template <typename Element>
sf::Vector2i Grid<Element>::normalize(sf::Vector2i pos) const {
    pos.x /= _cell_size.x;
    pos.y /= _cell_size.y;

    return pos;
}

template <typename Element>
Element& Grid<Element>::get(sf::Vector2i pos) const {
    return _elements[pos.y][pos.x];
}

template <typename Element>
void Grid<Element>::set(sf::Vector2i pos, const Element& item) {
    _elements[pos.y][pos.x] = item;
}

template <typename Element>
sf::Vector2i Grid<Element>::getSize() const {
    return _grid_size;
}

template <typename Element>
sf::Vector2i Grid<Element>::getCellSize() const {
    return _cell_size;
}

template <typename Element>
sf::Vector2i Grid<Element>::getCellPosition(sf::Vector2i pos) const {
    return sf::Vector2i(pos.x * _cell_size.x, pos.y * _cell_size.y);
}

template <typename Element>
bool Grid<Element>::occupyArea(sf::IntRect area) {
    _occupied_areas.push_back(area);
}

template <typename Element>
bool Grid<Element>::isOccupied(sf::IntRect area) const {
    for (int i = 0; i < _occupied_areas.size(); i++) {
        if (area.intersects(_occupied_areas[i]))
            return true;
    }

    return false;
}

template <typename Element>
bool Grid<Element>::isOutOfBound(sf::Vector2i pos) const {
    if (pos.x >= _grid_size.x || pos.y >= _grid_size.y) return true;
    return false;
}