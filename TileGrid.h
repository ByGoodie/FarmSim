#pragma once

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "SceneNode.h"
#include "Game.h"

class TileGrid : public SceneNode {
public:
    enum class TileType : int {
        Grass
    };

private:
    bool _edit_mode;
    Grid<TileType> _tiles;
    sf::RenderTexture _map;
    sf::Sprite _sprite;

    sf::IntRect getRectOf(TileType type) const;
    void constructGrid();
    void constructHouse();

public:
    TileGrid(Manager::Game::Texture& textures);

    void editModeSwitch();
    bool isEditable() const;
    
    void setTile(sf::Vector2i pos, TileType type);

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void onUpdate(sf::Time dt) override;
};