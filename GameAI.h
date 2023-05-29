#pragma once
#include "game.h"
#include "Menu.h"

class GameAI : public Game {
	bool isSelected = false;
	sf::Vector2f selectedCord;
	int index;
	int indexWhite;
	char col;
	int saveInt;
	int saveIntWhite;
	
public:
	GameAI(sf::RenderWindow& window);
	void playAI(sf::RenderWindow& window,Board board);
	sf::Vector2f randomMove(Board& board, sf::RenderWindow& window);
	int randomID();
	bool validMove(Piece* selectedPiece, sf::Vector2f cord, sf::Vector2f pos, Board& board, int index, sf::RenderWindow& window);
	
	int id;
	bool whichColorInfront(Board board, sf::Vector2f newPos);
	bool isAttak(Board board, sf::Vector2f newPos);
	
};



