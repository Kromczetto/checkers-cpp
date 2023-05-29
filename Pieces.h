#pragma once

#include <SFML/Graphics.hpp>


class Piece {
public:
    enum class Color { BLACK, WHITE, NONE };
    Piece(Color color, sf::Vector2f position, float radius,int ID);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    float getRadius() const;
    Color getColor() const;
    sf::CircleShape* getShape();
    bool isKing = false;
    bool alive = true;
    int getId();
    void setRadius(int rad);
    void setColor(Piece::Color c);
private:
    Color m_color;
    sf::CircleShape m_circle;
    sf::Vector2f m_position;
    float m_radius;
    int id;
};
