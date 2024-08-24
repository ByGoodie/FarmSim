#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <utility>

class Geometry {
public:
    enum class Edge {
        Left,
        Right,
        Top,
        Bottom
    };

    static float getLength(sf::Vector2f vector);
    static float getLengthSquared(sf::Vector2f vector);
    static sf::Vector2f normalize(sf::Vector2f vector);
    static bool checkSquareCollision(sf::Vector2f pos1, sf::Vector2f size1, sf::Vector2f pos2, sf::Vector2f size2);
    static sf::Vector2f getSquareNonCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f ns_sz, sf::Vector2f s_pn, sf::Vector2f s_sz);
    static bool checkRayVsSquareCollison(sf::Vector2f ray_p1, sf::Vector2f ray_p2, sf::Vector2f s_pos, sf::Vector2f s_size);
};

