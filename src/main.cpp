#include <iostream>
#include <SFML/Graphics.hpp>

#include "../include/Calculator.h"
#include "../include/DrawCalculator.h"

using namespace std;



int main() {

    std::string expr;

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

    }


}
