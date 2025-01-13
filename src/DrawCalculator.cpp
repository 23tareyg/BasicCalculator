#include "../include/DrawCalculator.h"
#include "../include/Calculator.h"

void DrawCalculator::drawNumpad() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++) {

        // App.draw etc
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(heightNumX, heightNumY));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition({heightNumX*j, (1000-heightNumY)-(heightNumY*i)});

        // draw items
        App.draw(rectangle);

        }
}



void DrawCalculator::drawOperators() {
    for (int i = 0; i < 5; i++) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(heightOperatorsX, heightOperatorsY));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition({390, (1000-heightOperatorsY)-(heightOperatorsY*i)});

        App.draw(rectangle);
    }
    
}
void DrawCalculator::drawClear() {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(heightNumX*3, heightNumY));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setOutlineThickness(2);
    rectangle.setPosition({0, 1000-(heightNumY*5)});

    App.draw(rectangle);

}
void DrawCalculator::drawFuncs() {
    for (int i = 0; i < 3; i++) {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(heightFunctionsX, heightFunctionsY));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition({i*heightFunctionsX, (1000) - (heightFunctionsY*6)});

        App.draw(rectangle); 
    }
}

void DrawCalculator::drawAll() {
    drawNumpad();
    drawOperators();
    drawClear();
    drawFuncs();
}
