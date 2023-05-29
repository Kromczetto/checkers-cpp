#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "Warcaby");

    Board board(sf::Vector2f(100, 100), 150, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    Piece* blackPiece1 = new Piece(Piece::Color::BLACK, sf::Vector2f(100, 100), 25);
    Piece* blackPiece2 = new Piece(Piece::Color::BLACK, sf::Vector2f(300, 100), 25);
    Piece* whitePiece1 = new Piece(Piece::Color::WHITE, sf::Vector2f(200, 200), 25);
    Piece* whitePiece2 = new Piece(Piece::Color::WHITE, sf::Vector2f(400, 200), 25);

    board.addPieces(blackPiece1);
    board.addPieces(blackPiece2);
    board.addPieces(whitePiece1);
    board.addPieces(whitePiece2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        board.draw(window);

        window.display();
    }

    return 0;
}
