// BİSMİLLAHHİRRAHMANİRRAHİM
//ALLAHUEKBER

#include "Geometry.h"

float Geometry::getLength(sf::Vector2f vector) {
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float Geometry::getLengthSquared(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

sf::Vector2f Geometry::normalize(sf::Vector2f vector) {
    return 1.f / getLength(vector) * vector;
}

bool Geometry::checkSquareCollision(sf::Vector2f pos1, sf::Vector2f size1, sf::Vector2f pos2, sf::Vector2f size2) {
    return ((pos1.x < pos2.x + size2.x) && (pos2.x < pos1.x + size1.x) &&
            (pos1.y < pos2.y + size2.y) && (pos2.y < pos1.y + size1.y));
}

sf::Vector2f Geometry::getSquareNonCollide(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f ns_sz, sf::Vector2f s_pos, sf::Vector2f s_size) {
    sf::Vector2f d = p2 - p1;

    float b1 = (s_pos.x - p1.x) / d.x;
    float a1 = p1.y - s_pos.y + b1 * d.y;   

    float b2 = (s_pos.y - p1.y) / d.y;
    float a2 = p1.x - s_pos.x + b2 * d.x;

    float b3 = (s_pos.x + s_size.x - p1.x) / d.x;
    float a3 = p1.y - s_pos.y + b3 * d.y;

    float b4 = (s_pos.y + s_size.y - p1.y) / d.y;
    float a4 = p1.x - s_pos.x + b4 * d.x;

    std::pair<sf::Vector2f, sf::Vector2f> intersect = std::make_pair(sf::Vector2f(NAN, NAN), sf::Vector2f(NAN, NAN));
    Edge edges[] = {Edge::Bottom, Edge::Bottom};

    if (a1 >= 0 && a1 <= s_size.y && 1 >= b1) {
        intersect.first = sf::Vector2f(s_pos.x, s_pos.y + a1);
        edges[0] = Edge::Left;
    }
    else if (a2 >= 0 && a2 <= s_size.x && 1 >= b2) {
        intersect.first = sf::Vector2f(s_pos.x + a2, s_pos.y);
        edges[0] = Edge::Top;
    }
    else if (a3 >= 0 && a3 <= s_size.y && 1 >= b3) {
        intersect.second = sf::Vector2f(s_pos.x + s_size.x, s_pos.y + a3);
        edges[1] = Edge::Right;
    }
    else if (a4 >= 0 && a4 <= s_size.x && 1 >= b4) {
        intersect.second = sf::Vector2f(s_pos.x + a4, s_pos.y + s_size.y);
        edges[1] = Edge::Bottom;
    }

    if (intersect.first.x == NAN && intersect.second.x == NAN) return p2;
    else if (intersect.first.x == NAN && intersect.second.x != NAN) {
        intersect.first = intersect.second;
        edges[0] = edges[1];
    }
    else if ((intersect.second.x != NAN) && (getLengthSquared(p1 - intersect.first) > getLengthSquared(p1 - intersect.second))) {
        intersect.first = intersect.second;
        edges[0] = edges[1];
    }

    sf::Vector2f result = sf::Vector2f(0.f, 0.f);

    if (edges[0] == Edge::Right) {
        result = sf::Vector2f(intersect.first.x + ns_sz.x, intersect.first.y);
    }
    else if (edges[0] == Edge::Left) {
        result = sf::Vector2f(intersect.first.x - ns_sz.x, intersect.first.y);
    }
     else if (edges[0] == Edge::Bottom) {
        result = sf::Vector2f(intersect.first.x, intersect.first.y + ns_sz.y);
    }
    else if (edges[0] == Edge::Top) {
        result = sf::Vector2f(intersect.first.x, intersect.first.y - ns_sz.y);
    }

    return result;
}

bool Geometry::checkRayVsSquareCollison(sf::Vector2f ray_p1, sf::Vector2f ray_p2, sf::Vector2f s_pos, sf::Vector2f s_size) {
    sf::Vector2f d = ray_p2 - ray_p1;

    float b1 = (s_pos.x - ray_p1.x) / d.x;
    float a1 = ray_p1.y - s_pos.y + b1 * d.y;   

    float b2 = (s_pos.y - ray_p1.y) / d.y;
    float a2 = ray_p1.x - s_pos.x + b2 * d.x;

    float b3 = (s_pos.x + s_size.x - ray_p1.x) / d.x;
    float a3 = ray_p1.y - s_pos.y + b3 * d.y;

    float b4 = (s_pos.y + s_size.y - ray_p1.y) / d.y;
    float a4 = ray_p1.x - s_pos.x + b4 * d.x;

    return ((a1 >= 0 && a1 <= s_size.y && 1 >= b1) ||
           (a2 >= 0 && a2 <= s_size.x && 1 >= b2) ||
            (a3 >= 0 && a3 <= s_size.y && 1 >= b3) ||
            (a4 >= 0 && a4 <= s_size.x && 1 >= b4));
}