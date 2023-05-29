#pragma once

#include <SFML/Graphics.hpp>
#include "Pieces.h"
#include <vector>

class Board {
    sf::Vector2f position;
    float size;
    sf::Color blackFile;
    sf::Color whiteFile;
    sf::RectangleShape boardSquare[8][8];
    std::vector<Piece> blackPieces;
    std::vector<Piece> whitePieces;
public:
    int findIndex(int x, int y);
    Board(sf::Vector2f boardPosition, float boardSize, sf::Color black, sf::Color white);
    void draw(sf::RenderWindow& window);
    void addPieces(Piece* piece);
    std::vector<Piece> copyVecBlack();
    std::vector<Piece> copyVecWhite();
    Piece* retValueOfBlack(int i);
    Piece* retValueOfWhite(int i);
    Piece* finder(int x, int y); 
    void movedBlack(std::vector<Piece>&vec,int i, sf::RenderWindow& window);
    void movedWhite(std::vector<Piece>&vec,int i, sf::RenderWindow& window);
    Piece* getPieceAtPosition(int x, int y); 
    Piece::Color findColor(int x, int y);

};
