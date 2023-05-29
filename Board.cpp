#include "Board.h"
#include <iostream>

Board::Board(sf::Vector2f boardPosition, float boardSize, sf::Color black, sf::Color white)
    :position(boardPosition), size(boardSize), blackFile(black), whiteFile(white) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(size, size));
            if ((i + j) % 2 == 0) square.setFillColor(black);
            else square.setFillColor(white);
            square.setPosition(boardPosition.x + boardSize * i, boardPosition.y + boardSize * j);
            boardSquare[i][j] = square;
        }
    }
}
void Board::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            window.draw(boardSquare[i][j]);
        }
    }
    for (auto& piece : blackPieces) {
        if(piece.alive)
        piece.draw(window);
    }

    for (auto& piece : whitePieces) {
        piece.draw(window);
    }
}
void Board::addPieces(Piece* piece) {
    int x = piece->getPosition().x / size;
    int y = piece->getPosition().y / size;

    piece->setPosition(boardSquare[x][y].getPosition() + sf::Vector2f(size / 2.f, size / 2.f));
    if (piece->getColor() == Piece::Color::BLACK) {
        blackPieces.push_back(*piece);
    }
    else {
        whitePieces.push_back(*piece);
    }
}


std::vector<Piece> Board::copyVecBlack() {
    return blackPieces;
}
std::vector<Piece> Board::copyVecWhite() {
    return whitePieces;
}
Piece* Board::retValueOfBlack(int i) {
    return &blackPieces[i];
}
Piece* Board::retValueOfWhite(int i) {
    return &whitePieces[i];
}

Piece* Board::finder(int x, int y) {
    for (int i = 0; i < 12; i++) {
        if (blackPieces[i].getPosition().x == x && blackPieces[i].getPosition().y == y)
            return &blackPieces[i];

        if (whitePieces[i].getPosition().x == x && whitePieces[i].getPosition().y == y)
            return &whitePieces[i];
    }
    return NULL;
}
int Board::findIndex(int x, int y) {
    for (int i = 0; i < 12; i++) {
        if (blackPieces[i].getPosition().x == x && blackPieces[i].getPosition().y == y)
            return i;
        if (whitePieces[i].getPosition().x == x && whitePieces[i].getPosition().y == y)
            return i;
    }
    return -1;
}
Piece::Color Board::findColor(int x, int y) {
    for (int i = 0; i < 12; i++) {
        if (blackPieces[i].getPosition().x == x && blackPieces[i].getPosition().y == y)
            return Piece::Color::BLACK;
        if (whitePieces[i].getPosition().x == x && whitePieces[i].getPosition().y == y)
            return Piece::Color::WHITE;
    }
    return Piece::Color::NONE;
}
void Board::movedBlack(std::vector<Piece>&vec,int i, sf::RenderWindow& window) {
    blackPieces[i] = vec[i];
    for (auto& piece : blackPieces) {
        piece.draw(window);
    }


}
void Board::movedWhite(std::vector<Piece>& vec, int i, sf::RenderWindow& window) {
    whitePieces[i] = vec[i];
    for (auto& piece : whitePieces) {
        piece.draw(window);
    }
}



Piece* Board::getPieceAtPosition(int x, int y) {
    for (auto& piece : blackPieces) {
        if (static_cast<int>(piece.getPosition().x / 150.f) == x && static_cast<int>(piece.getPosition().y / 150.f) == y) {
            return &piece;
        }
    }

    for (auto& piece : whitePieces) {
        if (static_cast<int>(piece.getPosition().x / 150.f) == x && static_cast<int>(piece.getPosition().y / 150.f) == y) {
            return &piece;
        }
    }

    return nullptr;
}
