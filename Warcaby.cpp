#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <iostream>






int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 1400), "Warcaby");

    
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
               window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    menu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    menu.opt(menu.selectedItemIndex,window);
                }
            }
        }

        window.clear();

        menu.draw(window);

        window.display();
    }
    

   
   
    
   
  
    return 0;
}
