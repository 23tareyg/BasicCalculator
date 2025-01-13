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

        // MAIN LOGIC FOR CALCULATOR
        sf::Mouse m;
        Calculator calc(expr, App, m);
        calc.handlePress();
        expr = calc.loadExpression();
        

       sf::Font font;
       font.loadFromFile("../resources/Quen.ttf");

       sf::Text text;
       text.setFont(font);
       text.setCharacterSize(60);
       text.setString(calc.loadExpression());
       App.draw(text);


        App.display();
    }
}
