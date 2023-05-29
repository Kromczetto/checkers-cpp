#include "Pieces.h"

Piece::Piece(Color color, sf::Vector2f position, float radius,int ID) :
    m_color(color), m_position(position), m_radius(radius), id(ID)
{
    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(position);
    if (color == Piece::Color::BLACK) {
        m_circle.setFillColor(sf::Color::Black);
    }
    else {
        m_circle.setFillColor(sf::Color::White);
    }
}
void Piece::setColor(Piece::Color c) {
    m_color = c;
}
void Piece::draw(sf::RenderWindow& window) {
    window.draw(m_circle);
    if (isKing) {
        m_circle.setOutlineThickness(3.f);
        m_circle.setOutlineColor(sf::Color::Yellow);
    }
}

void Piece::setPosition(sf::Vector2f position) {
    m_position = position;
    m_circle.setPosition(position);
}

sf::Vector2f Piece::getPosition() const {
    return m_position;
}
float Piece::getRadius() const {
    return m_radius;
}
sf::CircleShape* Piece::getShape() {
    return &m_circle;
}
Piece::Color Piece::getColor() const {
    return m_color;
}
int Piece::getId() {
    return id;
}
void Piece::setRadius(int rad) {
    m_radius=rad;
}