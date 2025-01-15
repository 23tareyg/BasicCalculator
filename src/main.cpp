#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/Calculator.h"
#include "../include/DrawCalculator.h"

using namespace std;
/*
FEATURES TO CONSIDER THIS "FINISHED"
1. [CHECK] put parenthesis blocks on screen
2. [CHECK] fix parenthesis segfaults "()"
3. [CHECK] add single parethesis automatically after entering in a trig function
4. get all text centered and properly displaying
5. implement color scheme, preferably through variables so it can be changed in only one location
6. implement a "last" button that loads in the previous answer number
7. [CHECK] fix 200ms input delay
8. fix functions grabbing everything after it unless parethesis

*/

int main() {

    sf::RenderWindow App(sf::VideoMode(600, 1000), "SFML_Project");

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
            App.close();
        }
        App.clear(sf::Color::Black);

        DrawCalculator c(App);
        c.drawAll();

        App.display();

        /*Calculator c;
        c.expression = "neg8+5";
        c.run();*/
    }
}

