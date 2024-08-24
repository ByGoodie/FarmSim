#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <functional>
#include "ResourceEnums.h"

class Animation {
private:
    sf::Texture* _texture;
    sf::Vector2i _sprite_size, _sheet_size;
    sf::IntRect _area;
    int _frame_count, _key_frame_count, _current_frame, _portions, _current_portion;

    std::function<sf::Color(int, int)> _color_fn; // First argument takes the current frame and second takes the total amount and produces a color based on the current over total.
    std::function<sf::Vector2f(int, int)> _pos_fn; // Same as color function.

public:
    Animation();
    Animation(sf::Vector2i sprite_size, int key_frame_count, int frame_count, sf::IntRect area, sf::Texture& texture, std::function<sf::Color(int, int)> color_fn, std::function<sf::Vector2f(int, int)> pos_fn);

    sf::Texture& getTexture() const;

    void setColorFn(std::function<sf::Color(int, int)> color_fn);
    void setPosFn(std::function<sf::Vector2f(int, int)> pos_fn);

    sf::IntRect getSpriteRect() const;
    sf::Color getColor() const;
    sf::Vector2f getLocalPosition() const;

    bool nextFrame();
    void reset();
};