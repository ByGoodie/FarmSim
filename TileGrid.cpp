#include "TileGrid.h"
#include <cstdlib>

TileGrid::TileGrid(Manager::Game::Texture& textures) : _tiles(sf::Vector2i(20, 10), sf::Vector2i(16, 16)) {
    _sprite.setTexture(textures[FarmSim::Texture::Game::MapTiles]);

    sf::Texture& tiles = textures[FarmSim::Texture::Game::MapTiles];

    sf::Vector2i map_size = _tiles.getCellPosition(_tiles.getSize());
    _map.create(map_size.x, map_size.y);

    constructGrid();
}

void TileGrid::constructGrid() {
    const sf::Texture& tiles = *_sprite.getTexture();
}

sf::IntRect TileGrid::getRectOf(TileType type) const {
    int offset = (int)type;

    return sf::IntRect(
        (offset * _tiles.getCellSize().x) % _tiles.getSize().x, (offset * _tiles.getCellSize().x) / _tiles.getSize().x * _tiles.getCellSize().y,
        _tiles.getCellSize().x, _tiles.getCellSize().y
    );
}

bool TileGrid::isEditable() const {
    return _edit_mode;
}

void TileGrid::editModeSwitch() {
    _edit_mode = !_edit_mode;
}

void TileGrid::setTile(sf::Vector2i pos, TileType type) {
    if (!_edit_mode) return;

    pos = _tiles.normalize(pos);

    if (_tiles.isOutOfBound(pos)) return;

    _tiles.set(pos, type);
}

void TileGrid::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
};

void TileGrid::onUpdate(sf::Time dt) {}