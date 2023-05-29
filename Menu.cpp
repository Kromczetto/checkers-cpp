#include "Menu.h"
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameAI.h"
#include "Stats.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Nie da sie wczytac czcionki" << std::endl;
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play 1vs1");
	menu[0].setPosition(sf::Vector2f((width-150) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Play with computer");
	menu[1].setPosition(sf::Vector2f((width - 150) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Statystyki");
	menu[2].setPosition(sf::Vector2f((width - 150) / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::opt(int x, sf::RenderWindow& window) {
	
	
	switch (x) {
	case 0: {
		Game Game(window);
	
		break;
	}
	case 1: {
		GameAI GameAI(window);
	
		break;
	}
	case 2:{
		Stats stats(window);
		
		break;
	}
	default:
		break;
	}
}