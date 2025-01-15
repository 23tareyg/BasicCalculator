#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/Calculator.h"
#include "../include/DrawCalculator.h"

using namespace std;

int main() {
    sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Basic Calculator");
    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
            App.close();
        }
        App.clear(sf::Color::Black); // set app background

        // instantiate and draw calculator
        DrawCalculator c(App);
        c.drawAll();

        App.display(); // display calculator
    }
}

/*Calculator c;
c.expression = "neg8+5";
c.run();*/