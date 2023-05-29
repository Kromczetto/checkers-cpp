#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pieces.h"
#include <vector>
#include <ranges>
#include <iostream>


class Game{
	bool isSelected = false;
    sf::Vector2f selectedCord;
	int index;
    int indexWhite;
	char col;
    int saveInt;
    int saveIntWhite;

    
public:
    enum class State { UNFINISHED, WIN_P1, WIN_P2 };
    int turn = 1;
	std::vector<Piece>vecBlack;
	std::vector<Piece>vecWhite;
	bool validMove(Piece* selectedPiece,sf::Vector2f selectedCord,sf::Vector2f pos,Board board,int index,sf::RenderWindow& window);
    sf::Vector2f beautify(sf::Vector2f pos);
    sf::Vector2f old;
    sf::Vector2f oldWhite;
	Game(sf::RenderWindow& window);
    Game();
   
    
    void killPiece(int x,int y, std::vector<Piece>&vecBlack, std::vector<Piece>&vecWhite,Board board,sf::Vector2f cords,sf::RenderWindow& window);
    Piece* finder(int x, int y, std::vector<Piece>&vecBlack, std::vector<Piece>&vecWhite,int index);
    
    int findPieceIndex(std::vector<Piece>& pieces, int x, int y);

    void attack(Piece* selectedPiece,sf::Vector2f cord, sf::Vector2f pos, Board board,sf::RenderWindow& window);
    void attackWhite(Piece* selectedPiece, sf::Vector2f cord, sf::Vector2f pos, Board board, sf::RenderWindow& window);
    void killPieceWhite(int x, int y, std::vector<Piece>& vecBlack, std::vector<Piece>& vecWhite, Board board, sf::Vector2f cords, sf::RenderWindow& window);
    int intReturner();
    int intReturnerWhite();
    void play(sf::RenderWindow& window, Board board);

    State endOfTheGame(std::vector<Piece>& vecBlack, std::vector<Piece>& vecWhite, sf::RenderWindow& window);
    void saveCords();
    void addCord(const std::string& nazwaPliku, const std::vector<std::string>& linie);

    std::vector<std::string>whiteCords;
    std::vector<std::string>blackCords;

    std::vector<int>whiteID;
    std::vector<int>blackID;

    bool isLetter(const std::string& tekst);
    void saveIdToFile(const std::string& path, std::vector<int>IDS);

   
};

