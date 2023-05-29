#include "Stats.h"
#include <iostream>
#include <string>
#include <ranges>
#include <fstream>


std::vector<std::string> Stats::readFromVec(const std::string& filename) {
    std::vector<std::string> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "B³¹d otwarcia pliku: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    file.close();
    return data;
}

Stats::Stats(sf::RenderWindow& window) {


    
    printWhite(window);


}
void Stats::printWhite(sf::RenderWindow& window) {
    std::vector<std::string> vec = readFromVec("ruchy/biale/plik_biale.txt");
    std::vector<std::string> readBlack = readFromVec("ruchy/czarne/plik_czarne.txt");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "B³¹d wczytywania czcionki." << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);

    std::string textContent = "Kordynatry bialych:\n";
    auto range = vec | std::views::transform([](const std::string& value) { return value + "\n"; });
    for (const auto& value : range) {
        textContent += value;
    }

    text.setString(textContent);

    sf::Text text2;
    text2.setFont(font);
    text2.setCharacterSize(24);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(1100, 100);

    std::string textContent2 = "Koordynaty czarnych:\n";
    auto rangeBlack = readBlack | std::views::transform([](const std::string& value) { return value + "\n"; });
    for (const auto& value : rangeBlack) {
        textContent2 += value;
    }

    text2.setString(textContent2);

    std::string sciezkaCzarne = "score/score_czarne.txt";
    std::string sciezkaBiale = "score/score_biale.txt";

    std::ifstream plikCzarne(sciezkaCzarne);
    std::ifstream plikBiale(sciezkaBiale);

    sf::Text textCzarne;
    sf::Text textBiale;

    if (plikCzarne.is_open() && plikBiale.is_open())
    {
        std::string czarneScore, bialeScore;
        std::getline(plikCzarne, czarneScore);
        std::getline(plikBiale, bialeScore);
        plikCzarne.close();
        plikBiale.close();

   

        
        textCzarne.setFont(font);
        textCzarne.setCharacterSize(30);
        textCzarne.setString("Liczba ruchow wykonanych przez czarne: " + czarneScore);
        textCzarne.setPosition(400, 100);

        
        textBiale.setFont(font);
        textBiale.setCharacterSize(30);
        textBiale.setString("Liczba ruchow wykonanych przez biale: " + bialeScore);
        textBiale.setPosition(400, 150);

       
    }
    else
    {
        std::cout << "Nie udalo sie otworzyc plikow" << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(text);
        window.draw(text2);
        window.draw(textBiale);
        window.draw(textCzarne);
        window.display();
    }
}
