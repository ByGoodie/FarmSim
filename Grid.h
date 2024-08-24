#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include <unordered_map>

template <typename Element>
class Grid {
private:
    std::vector<std::vector<Element>> _elements;
    sf::Vector2i _grid_size, _cell_size;
    std::vector<sf::IntRect> _occupied_areas;

public:
    Grid(sf::Vector2i grid_size, sf::Vector2i cell_size);

    sf::Vector2i normalize(sf::Vector2i pos) const;

    Element& get(sf::Vector2i pos) const;
    void set(sf::Vector2i pos, const Element& item);

    sf::Vector2i getSize() const;
    sf::Vector2i getCellSize() const;
    sf::Vector2i getCellPosition(sf::Vector2i pos) const;

    bool occupyArea(sf::IntRect area);
    bool isOccupied(sf::IntRect area) const;

    bool isOutOfBound(sf::Vector2i pos) const;
};