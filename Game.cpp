#include "Game.h"
#include <math.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <regex>
#include "win.h"
#include "Counter.h"

void Game::saveIdToFile(const std::string& path, std::vector<int>IDS) {
    std::ofstream plik(path, std::ios::trunc);

    if (plik.is_open())
    {
       
        for (const auto& linia : IDS)
        {
            plik << linia << "\n";
        }
        

        plik.close();
        
    }
    else
    {
        std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
    }
}

bool Game::isLetter(const std::string& tekst)
{
    std::regex wyrazenie("[a-zA-Z]");
    return !std::regex_search(tekst, wyrazenie);
}
void Game::addCord(const std::string& nazwaPliku, const std::vector<std::string>& linie){
    std::ofstream plik(nazwaPliku, std::ios::trunc);

    if (plik.is_open())
    {
        for (const auto& linia : linie)
        {
            plik << linia << "\n"; 
        }

        plik.close();
        
    }
    else
    {
        std::cout << "Nie udalo sie otworzyc pliku." << std::endl;
    }
}
void Game::saveCords() {
    
    std::filesystem::path baseDir = std::filesystem::current_path() / "ruchy";
    
    std::filesystem::create_directory(baseDir);
    std::string folderPath = baseDir.string();

    
    std::filesystem::create_directory(folderPath + "/biale");
    std::filesystem::create_directory(folderPath + "/czarne");
    std::filesystem::create_directories(folderPath + "/id/biale");
    std::filesystem::create_directories(folderPath + "/id/czarne");

    
  
    std::ofstream bialePlik("ruchy/biale/plik_biale.txt", std::ios::trunc);
    if (bialePlik.is_open()) {
        bialePlik << "Kordynaty bialych pionkow: " << std::endl;
        bialePlik.close();
    }

   
    std::ofstream czarnePlik("ruchy/czarne/plik_czarne.txt", std::ios::trunc);
    if (czarnePlik.is_open()) {
        czarnePlik << "Kordynaty czarnych pionkow: " << std::endl;
        czarnePlik.close();
    }
}

Piece* Game::finder(int x, int y, std::vector<Piece>&vecBlack, std::vector<Piece>&vecWhite,int index) {
    for (int i = 0; i < 12; i++) {
        if (vecBlack[i].getPosition().x == x && vecBlack[i].getPosition().y == y){

            return &vecBlack[i];
        }

        if (vecWhite[i].getPosition().x == x && vecWhite[i].getPosition().y == y){

            return &vecWhite[i];
        }

    }
    return NULL;
}

int Game::findPieceIndex(std::vector<Piece>& pieces, int x, int y) {
    for (int i = 0; i < 12; i++) {
        if (pieces[i].getPosition().x == x && pieces[i].getPosition().y == y)
            return i;
    }
    return NULL;
}

int Game::intReturner() {
    return saveInt;
}
void Game::killPiece(int x, int y, std::vector<Piece> &vecBlack, std::vector<Piece> &vecWhite,Board board,sf::Vector2f cords,sf::RenderWindow& window) {

    int currentX = static_cast<int>(cords.x / 150.f);
    int currentY = static_cast<int>(cords.y / 150.f);

    std::cout << x <<" "<< y  <<std::endl;
    if(x-currentX<0){ 
        x=x*150+25;
        y=(y-2)*150+25;
    } else{
        x=(x-2)*150+25;
        y=(y-2)*150+25;
    }


    std::cout << x <<" "<< y  <<std::endl;
        sf::Vector2f delVec(50,50);
        int _id = board.findIndex(x,y);
        if(_id == -1) return;
        std::cout << vecWhite[_id].getPosition().x << vecWhite[_id].getPosition().y<<std::endl;
        vecWhite[_id].setPosition(delVec);
        vecWhite[_id].setRadius(0);
        saveInt = _id;
        vecWhite[_id].alive = false;
        board.movedWhite(vecWhite,_id,window);
}
bool Game::validMove(Piece* selectedPiece,sf::Vector2f cord, sf::Vector2f pos, Board board,int index,sf::RenderWindow& window) {
    

    int x = static_cast<int>((pos.x) / 150.f);
    int y = static_cast<int>((pos.y) / 150.f);
    int currentX = static_cast<int>(cord.x / 150.f);
    int currentY = static_cast<int>(cord.y / 150.f);


    if (selectedPiece->getColor() == Piece::Color::BLACK && !selectedPiece->isKing) {
        if (x < 0 || y < 0 || x > 8 || y > 8) return false;
        if (currentX - x > 1 || currentY - y > 1)return false;

       if((x+1==currentX && y==currentY )||(x-1==currentX && currentY==y)) return false;
       if((x==currentX && y+1==currentY) || (x==currentX && y-1==currentY)) return false;
        if(x-currentX==2 || y-currentY==2){
            return true;
        }
       if(x-currentX>1 || y-currentY>1) return false;

        if (cord.y > pos.y)
            if (y > currentY) return true;
        else
            if (y < currentY) return false;

       return true;

    } else if (selectedPiece->getColor() == Piece::Color::WHITE && !selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >=8) return false;
        if((x+1==currentX && y==currentY )||(x-1==currentX && currentY==y)) return false;
        if((x==currentX && y+1==currentY) || (x==currentX && y-1==currentY)) return false;

        if (cord.y < pos.y)
            if (y < currentY) return true;
            else
            if (y > currentY) return false;

        return true;
    }
    if (selectedPiece->getColor() == Piece::Color::BLACK && selectedPiece->isKing) {
        if (x < 0 || y < 0 || x > 8 || y > 8) return false;

        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && currentY == y)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;
        if (x - currentX == -2 || y - currentY == -2) {
            return true;
        }
        if (x - currentX > 1 || y - currentY > 1) return false;
     
    
        return true;

    }
    else if (selectedPiece->getColor() == Piece::Color::WHITE && selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >= 8) return false;
        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && currentY == y)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;



        return true;
    }
}

void Game::attack(Piece* selectedPiece,sf::Vector2f cord, sf::Vector2f pos, Board board,sf::RenderWindow& window){
    int x = static_cast<int>((pos.x) / 150.f);
    int y = static_cast<int>((pos.y) / 150.f);
    int currentX = static_cast<int>(cord.x / 150.f);
    int currentY = static_cast<int>(cord.y / 150.f);

    if(x-currentX==2 || y-currentY==2){
      
            killPiece(x+1,y+1, vecBlack, vecWhite, board, cord, window);
            
       
    }
    if (x - currentX == -2 || y - currentY == 2) {
        killPiece(x - 1, y + 1, vecBlack, vecWhite, board, cord, window);
     
    }

}
void Game::attackWhite(Piece* selectedPiece, sf::Vector2f cord, sf::Vector2f pos, Board board, sf::RenderWindow& window) {
    int x = static_cast<int>((pos.x) / 150.f);
    int y = static_cast<int>((pos.y) / 150.f);
    int currentX = static_cast<int>(cord.x / 150.f);
    int currentY = static_cast<int>(cord.y / 150.f);
    std::cout << x << y << "ATAKI" << std::endl;
    std::cout << currentX << currentY << "BIERZACE" << std::endl;
    

    if (x-currentX == -2 || y- currentY == -2) {
       
               killPieceWhite(x - 1, y - 1, vecBlack, vecWhite, board, cord, window);
              
             
    }
   
}
void Game::killPieceWhite(int x, int y, std::vector<Piece>& vecBlack, std::vector<Piece>& vecWhite, Board board, sf::Vector2f cords, sf::RenderWindow& window) {

    int currentX = static_cast<int>(cords.x / 150.f);
    int currentY = static_cast<int>(cords.y / 150.f);

    std::cout << x << " " << y << std::endl;
    if (currentX-x < 0) { 
        x = x * 150 + 25;
        y = (y + 2) * 150 + 25;
    }
    else {
        x = (x + 2) * 150 + 25;
        y = (y + 2) * 150 + 25;
    }


   
    sf::Vector2f delVec(50, 50);
    int _id = board.findIndex(x, y);
    if (_id == -1) return;
    
   
    vecBlack[_id].getShape()->setFillColor(sf::Color::White);
    vecBlack[_id].setPosition(delVec);
    vecBlack[_id].alive = false;
    saveIntWhite = _id;
    board.movedBlack(vecBlack, _id, window);
}
int Game::intReturnerWhite() {
    return saveIntWhite;
}

sf::Vector2f Game::beautify(sf::Vector2f pos){
    pos.x -= 100;
    pos.y -= 100;

    int x = static_cast<int>((pos.x / 150.f)) * 150+175;
    int y = static_cast<int>((pos.y / 150.f)) * 150+175;

    return sf::Vector2f(x,y);
}

Game::State Game::endOfTheGame(std::vector<Piece>& vecBlack, std::vector<Piece>& vecWhite, sf::RenderWindow& window) {
    int sumBlack = 12;
    int sumWhite = 12;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Blad wczytywania czcionki." << std::endl;
       
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(200.f, 200.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
               
            }
        }

        sumBlack = 0;
        sumWhite = 0;
        for (int i = 0; i < 12; i++) {
            if (!vecBlack[i].alive)
                sumBlack++;
            if (!vecWhite[i].alive)
                sumWhite++;
        }

       

        if (sumBlack == 12) {
            break;
            window.clear();
            text.setString("Wygral pierwszy gracz");
            window.draw(text);
            window.display();
        }
        if (sumWhite == 12) {
            break;
            window.clear();
            text.setString("Wygral drugi gracz");
            window.draw(text);
            window.display();
            return State::WIN_P2;
        }

        return State::UNFINISHED;
    }

}


Game::Game() {

    Board board(sf::Vector2f(100, 100), 150, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
 

    Piece* blackPiece1 = new Piece(Piece::Color::BLACK, sf::Vector2f(100, 100), 50, 1);
    Piece* blackPiece2 = new Piece(Piece::Color::BLACK, sf::Vector2f(400, 100), 50, 2);
    Piece* blackPiece3 = new Piece(Piece::Color::BLACK, sf::Vector2f(700, 100), 50, 3);
    Piece* blackPiece4 = new Piece(Piece::Color::BLACK, sf::Vector2f(1000, 100), 50, 4);
    Piece* blackPiece5 = new Piece(Piece::Color::BLACK, sf::Vector2f(250, 200), 50, 5);
    Piece* blackPiece6 = new Piece(Piece::Color::BLACK, sf::Vector2f(550, 200), 50, 6);
    Piece* blackPiece7 = new Piece(Piece::Color::BLACK, sf::Vector2f(850, 200), 50, 7);
    Piece* blackPiece8 = new Piece(Piece::Color::BLACK, sf::Vector2f(1150, 200), 50, 8);
    Piece* blackPiece9 = new Piece(Piece::Color::BLACK, sf::Vector2f(100, 300), 50, 9);
    Piece* blackPiece10 = new Piece(Piece::Color::BLACK, sf::Vector2f(400, 300), 50, 10);
    Piece* blackPiece11 = new Piece(Piece::Color::BLACK, sf::Vector2f(700, 300), 50, 11);
    Piece* blackPiece12 = new Piece(Piece::Color::BLACK, sf::Vector2f(1000, 300), 50, 12);

    Piece* whitePiece1 = new Piece(Piece::Color::WHITE, sf::Vector2f(250, 1150), 50, 13);
    Piece* whitePiece2 = new Piece(Piece::Color::WHITE, sf::Vector2f(550, 1150), 50, 14);
    Piece* whitePiece3 = new Piece(Piece::Color::WHITE, sf::Vector2f(850, 1150), 50, 15);
    Piece* whitePiece4 = new Piece(Piece::Color::WHITE, sf::Vector2f(1150, 1150), 50, 16);
    Piece* whitePiece5 = new Piece(Piece::Color::WHITE, sf::Vector2f(100, 1000), 50, 17);
    Piece* whitePiece6 = new Piece(Piece::Color::WHITE, sf::Vector2f(400, 1000), 50, 18);
    Piece* whitePiece7 = new Piece(Piece::Color::WHITE, sf::Vector2f(700, 1000), 50, 19);
    Piece* whitePiece8 = new Piece(Piece::Color::WHITE, sf::Vector2f(1000, 1000), 50, 20);
    Piece* whitePiece9 = new Piece(Piece::Color::WHITE, sf::Vector2f(250, 850), 50, 21);
    Piece* whitePiece10 = new Piece(Piece::Color::WHITE, sf::Vector2f(550, 850), 50, 22);
    Piece* whitePiece11 = new Piece(Piece::Color::WHITE, sf::Vector2f(850, 850), 50, 23);
    Piece* whitePiece12 = new Piece(Piece::Color::WHITE, sf::Vector2f(1150, 850), 50, 24);

 



    std::thread blackThread([&]() {
        board.addPieces(blackPiece1);
        board.addPieces(blackPiece2);
        board.addPieces(blackPiece3);
        board.addPieces(blackPiece4);
        board.addPieces(blackPiece5);
        board.addPieces(blackPiece6);
        board.addPieces(blackPiece7);
        board.addPieces(blackPiece8);
        board.addPieces(blackPiece9);
        board.addPieces(blackPiece10);
        board.addPieces(blackPiece11);
        board.addPieces(blackPiece12);
        });


    std::thread whiteThread([&]() {
        board.addPieces(whitePiece1);
        board.addPieces(whitePiece2);
        board.addPieces(whitePiece3);
        board.addPieces(whitePiece4);
        board.addPieces(whitePiece5);
        board.addPieces(whitePiece6);
        board.addPieces(whitePiece7);
        board.addPieces(whitePiece8);
        board.addPieces(whitePiece9);
        board.addPieces(whitePiece10);
        board.addPieces(whitePiece11);
        board.addPieces(whitePiece12);
        });

    blackThread.join();
    whiteThread.join();


    for (int i = 0; i < 12; i++) {
        vecBlack.push_back(*board.retValueOfBlack(i));
        vecWhite.push_back(*board.retValueOfWhite(i));
    }

  
    
}

Game::Game(sf::RenderWindow& window) {

    saveCords();
    
   
    Board board(sf::Vector2f(100, 100), 150, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
  
   

    Piece* blackPiece1 = new Piece(Piece::Color::BLACK, sf::Vector2f(100, 100), 50, 1);
    Piece* blackPiece2 = new Piece(Piece::Color::BLACK, sf::Vector2f(400, 100), 50, 2);
    Piece* blackPiece3 = new Piece(Piece::Color::BLACK, sf::Vector2f(700, 100), 50, 3);
    Piece* blackPiece4 = new Piece(Piece::Color::BLACK, sf::Vector2f(1000, 100), 50, 4);
    Piece* blackPiece5 = new Piece(Piece::Color::BLACK, sf::Vector2f(250, 200), 50, 5);
    Piece* blackPiece6 = new Piece(Piece::Color::BLACK, sf::Vector2f(550, 200), 50, 6);
    Piece* blackPiece7 = new Piece(Piece::Color::BLACK, sf::Vector2f(850, 200), 50, 7);
    Piece* blackPiece8 = new Piece(Piece::Color::BLACK, sf::Vector2f(1150, 200), 50, 8);
    Piece* blackPiece9 = new Piece(Piece::Color::BLACK, sf::Vector2f(100, 300), 50, 9);
    Piece* blackPiece10 = new Piece(Piece::Color::BLACK, sf::Vector2f(400, 300), 50, 10);
    Piece* blackPiece11 = new Piece(Piece::Color::BLACK, sf::Vector2f(700, 300), 50, 11);
    Piece* blackPiece12 = new Piece(Piece::Color::BLACK, sf::Vector2f(1000, 300), 50, 12);

    Piece* whitePiece1 = new Piece(Piece::Color::WHITE, sf::Vector2f(250, 1150), 50, 13);
    Piece* whitePiece2 = new Piece(Piece::Color::WHITE, sf::Vector2f(550, 1150), 50, 14);
    Piece* whitePiece3 = new Piece(Piece::Color::WHITE, sf::Vector2f(850, 1150), 50, 15);
    Piece* whitePiece4 = new Piece(Piece::Color::WHITE, sf::Vector2f(1150, 1150), 50, 16);
    Piece* whitePiece5 = new Piece(Piece::Color::WHITE, sf::Vector2f(100, 1000), 50, 17);
    Piece* whitePiece6 = new Piece(Piece::Color::WHITE, sf::Vector2f(400, 1000), 50, 18);
    Piece* whitePiece7 = new Piece(Piece::Color::WHITE, sf::Vector2f(700, 1000), 50, 19);
    Piece* whitePiece8 = new Piece(Piece::Color::WHITE, sf::Vector2f(1000, 1000), 50, 20);
    Piece* whitePiece9 = new Piece(Piece::Color::WHITE, sf::Vector2f(250, 850), 50, 21);
    Piece* whitePiece10 = new Piece(Piece::Color::WHITE, sf::Vector2f(550, 850), 50, 22);
    Piece* whitePiece11 = new Piece(Piece::Color::WHITE, sf::Vector2f(850, 850), 50, 23);
    Piece* whitePiece12 = new Piece(Piece::Color::WHITE, sf::Vector2f(1150, 850), 50, 24);

    std::thread blackThread([&]() {
        board.addPieces(blackPiece1);
        board.addPieces(blackPiece2);
        board.addPieces(blackPiece3);
        board.addPieces(blackPiece4);
        board.addPieces(blackPiece5);
        board.addPieces(blackPiece6);
        board.addPieces(blackPiece7);
        board.addPieces(blackPiece8);
        board.addPieces(blackPiece9);
        board.addPieces(blackPiece10);
        board.addPieces(blackPiece11);
        board.addPieces(blackPiece12);
        });

    

    std::thread whiteThread([&]() {
        board.addPieces(whitePiece1);
        board.addPieces(whitePiece2);
        board.addPieces(whitePiece3);
        board.addPieces(whitePiece4);
        board.addPieces(whitePiece5);
        board.addPieces(whitePiece6);
        board.addPieces(whitePiece7);
        board.addPieces(whitePiece8);
        board.addPieces(whitePiece9);
        board.addPieces(whitePiece10);
        board.addPieces(whitePiece11);
        board.addPieces(whitePiece12);
        });

    blackThread.join();
    whiteThread.join();

    for (int i = 0; i < 12; i++) {
        vecBlack.push_back(*board.retValueOfBlack(i));
        vecWhite.push_back(*board.retValueOfWhite(i));
    }

   
    play(window, board);
}
void Game::play(sf::RenderWindow& window, Board board){
    Counter counter;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            
            if(endOfTheGame(vecBlack, vecWhite, window)!=State::UNFINISHED);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (int i = 0; i < 12; i++) {
                    
                    
                    if (vecBlack[i].getShape()->getGlobalBounds().contains(mousePosition)) {
                        if (vecBlack[i].alive) {
                            isSelected = true;
                           
                            selectedCord = vecBlack[i].getPosition();
                            index = i;
                            old.x = vecBlack[index].getPosition().x;
                            old.y = vecBlack[index].getPosition().y;
                            col = 'b';

                        }
                    }
                    
                    else if (vecWhite[i].getShape()->getGlobalBounds().contains(mousePosition)) {
                        if (vecWhite[i].alive) {
                            isSelected = true;
                            selectedCord = vecWhite[i].getPosition();
                            index = i;
                            oldWhite.x = vecWhite[index].getPosition().x;
                            oldWhite.y = vecWhite[index].getPosition().y;
                            col = 'w';
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved && isSelected) {
                sf::Vector2f mousPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f newPos = selectedCord + mousPos - selectedCord - sf::Vector2f(vecBlack[index].getRadius(), vecBlack[index].getRadius());
                if (col == 'b') {

                        vecBlack[index].setPosition(newPos);
                        vecBlack[index].getShape()->setOutlineThickness(5.f);
                        vecBlack[index].getShape()->setOutlineColor(sf::Color::Blue);

               };
                if (col == 'w') {
                    
                        vecWhite[index].setPosition(newPos);
                        vecWhite[index].getShape()->setOutlineThickness(5.f);
                        vecWhite[index].getShape()->setOutlineColor(sf::Color::Blue);
                    
                }
               
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isSelected = false;
                
                sf::Vector2f mousPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f newPos = selectedCord + mousPos - selectedCord - sf::Vector2f(vecBlack[index].getRadius(), vecBlack[index].getRadius());
                if (col == 'b') {
                  
                    float xV = beautify(newPos).x;
                    float yV = beautify(newPos).y;
                    sf::Vector2f validVec(xV,yV);

                    if(turn==2)
                    if (validMove(&vecBlack[index], old, validVec, board, index, window)) {

                        vecBlack[index].setPosition(beautify(newPos));
                        vecBlack[index].getShape()->setOutlineThickness(0);
                        board.movedBlack(vecBlack, index, window);
                        attack(&vecBlack[index], old, validVec, board, window);
                        board.movedWhite(vecWhite, intReturner(),window);
                        std::stringstream ss;
                        ss << validVec.x << " " << validVec.y;
                        std::string c = ss.str();

                        blackCords.push_back(c);
                        blackID.push_back(index);
                        if (isLetter(c)) std::cout << "Polozenie nie zawiera liter";
                        
                        addCord("ruchy/czarne/plik_czarne.txt", blackCords);
                        saveIdToFile("ruchy/id/czarne/id_czarne.txt",blackID);
                        counter.inBlack();
                        counter.saveScore();
                        
                        turn = ((turn == 1) ? 2 : 1);
                    } else {
                  
                        vecBlack[index].setPosition(beautify(old));
                        vecBlack[index].getShape()->setOutlineThickness(0);
                        board.movedBlack(vecBlack, index, window);
                    }
                    else{
                        vecBlack[index].setPosition(beautify(old));
                        vecBlack[index].getShape()->setOutlineThickness(0);
                        board.movedBlack(vecBlack, index, window);
                    }

                }
                if(turn==1){
                if (col == 'w') {
                   
                    float xV = beautify(newPos).x;
                    float yV = beautify(newPos).y;
                    
                 
                    sf::Vector2f validVec(xV,yV);
                    if(validMove(&vecWhite[index],oldWhite, validVec,board,index,window)){
                        vecWhite[index].setPosition(beautify(newPos));
                        vecWhite[index].getShape()->setOutlineThickness(0);
                        board.movedWhite(vecWhite, index, window);
                       
                         attackWhite(&vecWhite[index], oldWhite, validVec, board, window);
                        board.movedBlack(vecBlack, intReturnerWhite(), window);


                        std::stringstream ss;
                        ss << validVec.x << " " << validVec.y;
                        std::string c = ss.str();

                        if (isLetter(c)) std::cout << "Polozenie nie zawiera liter";

                        whiteCords.push_back(c);
                        whiteID.push_back(index);
                        addCord("ruchy/biale/plik_biale.txt", whiteCords);
                        saveIdToFile("ruchy/id/biale/id_biale.txt", whiteID);
                        counter.inWhite();
                        counter.saveScore();
                        turn = ((turn == 1) ? 2 : 1);
                    } else{
                      
                        vecWhite[index].setPosition(beautify(oldWhite));
                        vecWhite[index].getShape()->setOutlineThickness(0);
                        board.movedWhite(vecWhite, index, window);
                    }
                }}
                else{
                    vecWhite[index].setPosition(beautify(oldWhite));
                    vecWhite[index].getShape()->setOutlineThickness(0);
                    board.movedWhite(vecWhite, index, window);
                }
            }
        }

        window.clear(sf::Color::White);

        board.draw(window);

        for (int i = 0; i < 12; i++) {
            if (vecBlack[i].getPosition().y >= 1150)
                vecBlack[i].isKing = true; 
   
               
            if (vecWhite[i].getPosition().y <= 250)
                vecWhite[i].isKing = true; 
           
        }
        
      
        for (int i = 0; i < 12; i++) {

            window.draw(*vecBlack[i].getShape());
            window.draw(*vecWhite[i].getShape());
 
        }

        window.display();
    }

}
