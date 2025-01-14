#include "../include/DrawCalculator.h"
#include "../include/Calculator.h"

Calculator calc;
dispMode display;
bool wait;

void DrawCalculator::drawNumpad() {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++) {
            // Set constants
            float xPos = heightNumX*j;
            float yPos = (1000-heightNumY) - (heightNumY*i);

            // Draw rectangles
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(heightNumX, heightNumY));
            rectangle.setFillColor(sf::Color::White);
            rectangle.setOutlineColor(sf::Color::Green);
            rectangle.setOutlineThickness(2);
            rectangle.setPosition({xPos, yPos});

            // Draw text
            sf::Text text;
            text.setFont(font);
            text.setFillColor(sf::Color::Blue);
            text.setCharacterSize(30);
            text.setString(numButtons.at(j + 3*i));
            text.setPosition({xPos, yPos});

            // draw items
            App.draw(rectangle);
            App.draw(text);

        }
}

void DrawCalculator::drawOperators() {
    for (int i = 0; i < 5; i++) {
        float xPos = 390;
        float yPos = (1000-OP_HEIGHT) - (OP_HEIGHT*i);
        sf::Text text;

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(OP_WIDTH, OP_HEIGHT));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition({xPos, yPos});


        drawStandText(text, font, sf::Color::Blue, 35, operators.at(i));
        sf::FloatRect rect = text.getLocalBounds();
        float centerX = ((OP_WIDTH - rect.width) / 2.0f) + xPos;
        float centerY = ((OP_HEIGHT - rect.height) / 2.0f) + yPos;
        text.setPosition(centerX, centerY);

        App.draw(rectangle);
        App.draw(text);
    }
    
}

void DrawCalculator::drawFuncs() {
    for (int i = 0; i < 3; i++) {
        float xPos = i*heightFunctionsX;
        float yPos = (1000) - (heightFunctionsY*6);
        sf::Text text;

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(heightFunctionsX, heightFunctionsY));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Green);
        rectangle.setOutlineThickness(2);
        rectangle.setPosition({xPos, yPos});

        drawStandText(text, font, sf::Color::Blue, 35, functions.at(i));
        sf::FloatRect rect = text.getLocalBounds();
        float centerX = ((FUNC_WIDTH - rect.width) / 2.0f) + xPos;
        float centerY = ((FUNC_HEIGHT - rect.height) / 2.0f) + yPos;
        text.setPosition(centerX, centerY);
        
        App.draw(rectangle); 
        App.draw(text);
    }
}

void DrawCalculator::handlePress() {
    sf::Text text;
    if (!calc.getMouseNum(mouse.getPosition(App)).empty() && mouse.isButtonPressed(sf::Mouse::Button::Left)) {
        wait = true;
        if (calc.getMouseNum(mouse.getPosition(App)) == "CLEAR") {
            calc.clear();
            display = dispMode::CLEAR;
        } else if (calc.getMouseNum(mouse.getPosition(App)) == "ENTER") {
            try {    
                calc.run();
                display = dispMode::ANSWER;
                calc.clear();
            } catch (...) {
                display = dispMode::ERR;
                calc.clear();
            }
    } else {
            calc.expression += (calc.getMouseNum(mouse.getPosition(App)));
            display = dispMode::EXPR;
        }
        std::cout << calc.expression << std::endl;
    }

    if (display == dispMode::ANSWER) {
        drawStandText(text, font, sf::Color::White, 60, std::to_string(calc.ans));
    } else if (display == dispMode::EXPR) {
        drawStandText(text, font, sf::Color::White, 60, calc.expression);
    } else if (display == dispMode::CLEAR) {
        drawStandText(text, font, sf::Color::White, 60, "clear");
    } else if (display == dispMode::ERR) {
        drawStandText(text, font, sf::Color::White, 60, "err");
    }
    
    App.draw(text);
    App.display();

    if (wait) {
        wait = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } 
}


void DrawCalculator::drawAll() {
    drawNumpad();
    drawOperators();
    drawFuncs();
    handlePress();
}


