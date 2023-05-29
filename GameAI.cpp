#include "GameAI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

bool GameAI::validMove(Piece* selectedPiece, sf::Vector2f cord, sf::Vector2f pos, Board& board, int index, sf::RenderWindow& window) {
    int x = static_cast<int>((pos.x) / 150.f);
    int y = static_cast<int>((pos.y) / 150.f);
    int currentX = static_cast<int>(cord.x / 150.f);
    int currentY = static_cast<int>(cord.y / 150.f);

    if (selectedPiece->getColor() == Piece::Color::BLACK && !selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >= 8) {
            if (isAttak(board, pos)) return true;
            if (x == currentX + 1 && y == currentY + 1) {
                return true;
            }
            else if (x == currentX - 1 && y==currentY+1) {
                return true;
            }
            else {
                return false;
            }
        }

        if (x < 0 || y < 0 || x >= 8 || y >= 8) return false;
        if (std::abs(currentX - x) > 1 || std::abs(currentY - y) > 1) return false;
        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && y == currentY)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;

        if (std::abs(x - currentX) == 2 && std::abs(y - currentY) == 2) {
            
            int capturedX = (currentX + x) / 2;
            int capturedY = (currentY + y) / 2;
            const Piece* capturedPiece = board.getPieceAtPosition(capturedX, capturedY);
            if (!capturedPiece || selectedPiece->getColor() == capturedPiece->getColor()) return false;

         
        }
        if (board.getPieceAtPosition(x, y) != nullptr) return false; 

        if (cord.y < pos.y) {
            if (y > currentY) return true;
            else return false;
        }
        else {
            if (y < currentY) return true;
            else return false;
        }
    }
    else if (selectedPiece->getColor() == Piece::Color::WHITE && !selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >= 8) return false;
        if (std::abs(currentX - x) > 1 || std::abs(currentY - y) > 1) return false;
        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && y == currentY)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;

        if (std::abs(x - currentX) == 2 && std::abs(y - currentY) == 2) {
          
            int capturedX = (currentX + x) / 2;
            int capturedY = (currentY + y) / 2;
            const Piece* capturedPiece = board.getPieceAtPosition(capturedX, capturedY);
            if (!capturedPiece || selectedPiece->getColor() == capturedPiece->getColor()) return false;

          
        }
        if (board.getPieceAtPosition(x, y) != nullptr) return false; 

        if (cord.y > pos.y) {
            if (y < currentY) return true;
            else return false;
        }
        else {
            if (y > currentY) return true;
            else return false;
        }
    }
    else if (selectedPiece->getColor() == Piece::Color::BLACK && selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >= 8) return false;
        if (std::abs(currentX - x) > 1 || std::abs(currentY - y) > 1) return false;
        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && y == currentY)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;

        if (std::abs(x - currentX) == 2 && std::abs(y - currentY) == 2) {
         
            int capturedX = (currentX + x) / 2;
            int capturedY = (currentY + y) / 2;
            const Piece* capturedPiece = board.getPieceAtPosition(capturedX, capturedY);
            if (!capturedPiece || selectedPiece->getColor() == capturedPiece->getColor()) return false;

         
        }
        if (board.getPieceAtPosition(x, y) != nullptr) return false; 

        return true;
    }
    else if (selectedPiece->getColor() == Piece::Color::WHITE && selectedPiece->isKing) {
        if (x < 0 || y < 0 || x >= 8 || y >= 8) return false;
        if (std::abs(currentX - x) > 1 || std::abs(currentY - y) > 1) return false;
        if ((x + 1 == currentX && y == currentY) || (x - 1 == currentX && y == currentY)) return false;
        if ((x == currentX && y + 1 == currentY) || (x == currentX && y - 1 == currentY)) return false;

        if (std::abs(x - currentX) == 2 && std::abs(y - currentY) == 2) {
            
            int capturedX = (currentX + x) / 2;
            int capturedY = (currentY + y) / 2;
            const Piece* capturedPiece = board.getPieceAtPosition(capturedX, capturedY);
            if (!capturedPiece || selectedPiece->getColor() == capturedPiece->getColor()) return false;

          
        }
        if (board.getPieceAtPosition(x, y) != nullptr) return false; 

        return true;
    }

    return false;
}

int GameAI::randomID() {
    static bool srandCalled = false;
    if (!srandCalled) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        srandCalled = true;
    }

    int randomNumber = std::rand() % 12;
    return randomNumber;
}

bool GameAI::whichColorInfront(Board board,sf::Vector2f newPos) {
    Piece::Color tempColor = board.findColor(newPos.x, newPos.y);
    if (tempColor == Piece::Color::NONE)
        return true;
    return false;
}
bool GameAI::isAttak(Board board, sf::Vector2f newPos) {
    Piece::Color tempFirst = board.findColor(newPos.x, newPos.y);
    Piece::Color tempSecond = board.findColor(newPos.x+150.f, newPos.y+150.f);
    if (tempSecond != Piece::Color::BLACK && tempSecond != Piece::Color::WHITE && tempFirst == Piece::Color::WHITE)
        return true;
  
    tempSecond = board.findColor(newPos.x - 150.f, newPos.y + 150.f);
    if (tempSecond == Piece::Color::NONE && tempFirst == Piece::Color::WHITE)
        return true;
    return false;
}
sf::Vector2f GameAI::randomMove(Board& board, sf::RenderWindow& window) {
    bool srandCalled = false;
    if (!srandCalled) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        srandCalled = true;
    }
    sf::Vector2f oldCords(1.f, 1.f);
    sf::Vector2f newCords(1.f, 1.f);
    int _ID;
    sf::Vector2f cordsToSave;
  
    do {

        do {

         _ID = randomID();
         id = _ID;
         int tempX = static_cast<int>(vecBlack[_ID].getPosition().x/150.f);
         int tempY = static_cast<int>(vecBlack[_ID].getPosition().y/150.f);


         oldCords.x = tempX;
         oldCords.y = tempY;
         
         float newX=tempX;
         float newY=tempY;
       
         bool site;
         site = std::rand() % 2;
         if (newX <= 1) {
             newX += 1;
             newY += 1;
         }
         else if (newX>= 8) {
              newX -= 1;
             newY += 1;
         }
         else {

         if (site) {
             
             newX += 1;
             newY += 1;
             sf::Vector2f nC;
             nC.x = newX * 150.f + 25.f;
             nC.y = newY * 150.f + 25.f;
             if (isAttak(board, nC)) {
                 newCords.x = newX+1;
                 newCords.y = newY+1;
                 sf::Vector2f oldd;
                 oldd.x = tempX;
                 oldd.y = tempY;
                 attack(&vecBlack[id], oldd, newCords, board, window);
                 
                 int TX = oldd.x+1;
                 int TY = oldd.y+1;
                 
                

                 int tempID = board.getPieceAtPosition(TX, TX)->getId() - 13;
                 
                 sf::Vector2f deleteCordsTemp(1.f, 1.f);
                 vecWhite[tempID].setPosition(deleteCordsTemp);
                 vecWhite[tempID].setRadius(0);
                 vecWhite[tempID].alive = false;
                 board.movedWhite(vecWhite, tempID, window);
                 
                
                 break;
             }
         }
         if (!site) {

             newX -= 1;
             newY += 1;
             sf::Vector2f nC;
             nC.x = newX * 150.f + 25.f;
             nC.y = newY * 150.f + 25.f;
             if (isAttak(board, nC)) {
                 newCords.x = newX - 1;
                 newCords.y = newY + 1;
                 sf::Vector2f oldd;
                 oldd.x = tempX;
                 oldd.y = tempY;
                 attack(&vecBlack[id], oldd, newCords, board, window);
                 
                 int TX = oldd.x - 1;
                 int TY = oldd.y + 1;
                 
                 int tempID = board.getPieceAtPosition(TX, TX)->getId() - 13;
                 sf::Vector2f deleteCordsTemp(1.f, 1.f);
                 vecWhite[tempID].setPosition(deleteCordsTemp);
                 vecWhite[tempID].setRadius(0);
                 vecWhite[tempID].alive = false;
                 board.movedWhite(vecWhite, tempID, window);

               
                 break;
             }
         }
         }
             

         newCords.x = newX;
         newCords.y = newY;

        

         
         cordsToSave.x = newCords.x * 150.f + 25.f;
         cordsToSave.y = newCords.y * 150.f + 25.f;
        } while (!whichColorInfront(board, cordsToSave));
        
        
        
    } while (validMove(&vecBlack[_ID], oldCords, newCords, board, _ID, window));

   
    
   
    newCords.x *= 150.f;
    newCords.x += 25.f;
    newCords.y *= 150.f;
    newCords.y += 25.f;
  
    return newCords;
}



GameAI::GameAI(sf::RenderWindow& window)  {

   
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

    for (int i = 0; i < 12; i++) {
        vecBlack.push_back(*board.retValueOfBlack(i));
        vecWhite.push_back(*board.retValueOfWhite(i));
    }

    
    GameAI::playAI(window, board);
}

void GameAI::playAI(sf::RenderWindow& window, Board board) {
    int turn = 1;  
    bool isSelected = false;
    int selectedPieceIndex = -1;
    sf::Vector2f selectedPiecePosition;
    char selectedPieceColor = ' ';

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (endOfTheGame(vecBlack, vecWhite, window) == State::UNFINISHED)
                std::cout << "";

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (turn == 1) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    for (int i = 0; i < 12; i++) {
                        if (vecWhite[i].getShape()->getGlobalBounds().contains(mousePosition)) {
                            if (vecWhite[i].alive) {
                                isSelected = true;
                                selectedPiecePosition = vecWhite[i].getPosition();
                                selectedPieceIndex = i;
                                selectedPieceColor = 'w';
                                vecWhite[i].getShape()->setOutlineThickness(5.f);
                                vecWhite[i].getShape()->setOutlineColor(sf::Color::Blue);
                            }
                        }
                    }
                }

                if (event.type == sf::Event::MouseMoved && isSelected) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::Vector2f newPos = selectedPiecePosition + mousePos - selectedPiecePosition - sf::Vector2f(vecBlack[selectedPieceIndex].getRadius(), vecBlack[selectedPieceIndex].getRadius());

                    if (selectedPieceColor == 'w') {
                        vecWhite[selectedPieceIndex].setPosition(newPos);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    isSelected = false;
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::Vector2f newPos = selectedPiecePosition + mousePos - selectedPiecePosition - sf::Vector2f(vecBlack[selectedPieceIndex].getRadius(), vecBlack[selectedPieceIndex].getRadius());

                    if (selectedPieceColor == 'w') {
                        float xV = beautify(newPos).x;
                        float yV = beautify(newPos).y;
                        sf::Vector2f validVec(xV, yV);

                        if (Game::validMove(&vecWhite[selectedPieceIndex], selectedPiecePosition, validVec, board, selectedPieceIndex, window)) {
                            vecWhite[selectedPieceIndex].setPosition(beautify(newPos));
                            vecWhite[selectedPieceIndex].getShape()->setOutlineThickness(0);
                            board.movedWhite(vecWhite, selectedPieceIndex, window);
                            attackWhite(&vecWhite[selectedPieceIndex], selectedPiecePosition, validVec, board, window);
                            board.movedBlack(vecBlack, intReturnerWhite(), window);
                            turn = 2;
                        }
                        else {
                            vecWhite[selectedPieceIndex].setPosition(beautify(selectedPiecePosition));
                            vecWhite[selectedPieceIndex].getShape()->setOutlineThickness(0);
                            board.movedWhite(vecWhite, selectedPieceIndex, window);
                        }
                    }
                }
            }
            else if (turn == 2) {
              
                sf::Vector2f newPosVec(randomMove(board,window));
               

                std::cout << newPosVec.x << ' ' << newPosVec.y;

                vecBlack[id].setPosition(newPosVec);
                vecBlack[id].getShape()->setOutlineThickness(0);
                board.movedBlack(vecBlack, id, window);
          
                turn = 1;
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
