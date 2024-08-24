#include <SFML/Graphics.hpp>
#include <iostream>
#include "Geometry.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080) ,"Window");
    sf::Event evnt;

    sf::Vector2f ref(0.f, 0.f);
    sf::Vector2f pos(0.f, 0.f);
    sf::RectangleShape rect(sf::Vector2f(100.f, 50.f)), side_rect(sf::Vector2f(20.f, 20.f));
    rect.setPosition(sf::Vector2f(560.f, 300.f));
    rect.setFillColor(sf::Color::White);
    side_rect.setFillColor(sf::Color::Green);
    side_rect.setPosition(sf::Vector2f(-100.f, -100.f));
    sf::Vertex line[] = {{{0, 0}, sf::Color::Black}, {{0, 0}, sf::Color::Black}};

    while (window.isOpen()) {
        window.pollEvent(evnt);
        if (evnt.type == sf::Event::Closed) window.close();
        else if (evnt.type == sf::Event::MouseMoved) {
            pos.x = evnt.mouseMove.x;
            pos.y = evnt.mouseMove.y;
            line[1].position.x = evnt.mouseMove.x;
            line[1].position.y = evnt.mouseMove.y;
        }
        else if (evnt.type == sf::Event::MouseButtonReleased) {
            ref.x = evnt.mouseButton.x;
            ref.y = evnt.mouseButton.y;
            line[0].position.x = evnt.mouseButton.x;
            line[0].position.y = evnt.mouseButton.y;
        }

        window.clear(sf::Color::Blue);
        window.draw(rect);
        window.draw(side_rect);
        window.draw(line, 2, sf::Lines);
        window.display();

        if (Geometry::checkRayVsSquareCollison(ref, pos, rect.getPosition(), rect.getSize())) {
            rect.setFillColor(sf::Color::Red);

            side_rect.setPosition(Geometry::getSquareNonCollide(ref, pos, side_rect.getSize(), rect.getPosition(), rect.getSize()));
        }
        else {
            rect.setFillColor(sf::Color::White);
            side_rect.setPosition(sf::Vector2f(-100.f, -100.f));
        }
    }

    return 0;
}