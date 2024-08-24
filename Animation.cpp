#include "Animation.h"

Animation::Animation() {}

Animation::Animation(sf::Vector2i sprite_size, int key_frame_count, int frame_count, sf::IntRect area, sf::Texture& texture, std::function<sf::Color(int, int)> color_fn, std::function<sf::Vector2f(int, int)> pos_fn) : _texture(&texture) {
    _texture = &texture;
    
    _sheet_size.x = texture.getSize().x / sprite_size.x;
    _sheet_size.y = texture.getSize().y / sprite_size.y;

    _key_frame_count = key_frame_count;
    _frame_count = frame_count;
    _sprite_size = sprite_size;
    _current_frame = 0;
    _area = area;

    _color_fn = color_fn;
    _pos_fn = pos_fn;
}

/*
constexpr Animation Animation::operator=(const Animation&& other) {
    this->_texture = other._texture;
    this->_area = other._area;
    this->_color_fn = other._color_fn;
    this->_pos_fn = other._pos_fn;
    this->_current_frame = other._current_frame;
    this->_current_portion = other._current_portion;
}
*/

sf::Texture& Animation::getTexture() const {
    return *_texture;
}

void Animation::setColorFn(std::function<sf::Color(int, int)> color_fn) {
    _color_fn = color_fn;
}

void Animation::setPosFn(std::function<sf::Vector2f(int, int)> pos_fn) {
    _pos_fn = pos_fn;
}

sf::IntRect Animation::getSpriteRect() const {
    int key_frame = _current_frame * _key_frame_count / _frame_count;

    return sf::IntRect(
        (_area.left + key_frame) % _sheet_size.x * _sprite_size.x, (_area.top + (_area.left + key_frame) / _sheet_size.x) * _sprite_size.y,
        _sprite_size.x, _sprite_size.y
    );
}

sf::Color Animation::getColor() const {
    return _color_fn(_current_frame, _frame_count);
}

sf::Vector2f Animation::getLocalPosition() const {
    return (_pos_fn == nullptr) ? (sf::Vector2f(0.f, 0.f)) : (_pos_fn(_current_frame, _frame_count));
}

bool Animation::nextFrame() {
    _current_frame = (_current_frame + 1) % _frame_count;

    return _current_frame == 0;
}

void Animation::reset() {
    _current_frame = 0;
}