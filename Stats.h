#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ranges>
#include <string>

class Stats {
public:
	Stats(sf::RenderWindow& window);
	std::vector<std::string> readFromVec(const std::string& filename);
	void printWhite(sf::RenderWindow& window);
	
};

