#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Calculator.h"
#include "Constants.h"

using namespace CalculatorConst;


class DrawCalculator {
public:
    DrawCalculator() = delete;
    DrawCalculator(sf::RenderWindow& a) : App(a) {
        int heightNumX = NUM_WIDTH;
        int heightNumY = NUM_HEIGHT;
        int heightOperatorsX = OP_WIDTH;
        int heightOperatorsY = OP_HEIGHT;
        int heightFunctionsX = FUNC_WIDTH;
        int heightFunctionsY = FUNC_HEIGHT;
        font.loadFromFile("../resources/Quen.ttf");
    }

    void drawNumpad();
    void drawOperators();
    void drawFuncs();
    void handlePress();
    void drawAll();

private:
    // all refer to height of a single "button"
    int heightNumX = 130;
    int heightNumY = 130;
    int heightOperatorsX = 210;
    int heightOperatorsY = 130;
    int heightFunctionsX = 200;
    int heightFunctionsY = 130;

    std::vector<std::string> drawableOperators = {"=", "+", "-", "x", "/"};
    std::vector<std::string> drawableFunctions = {"sin", "cos", "tan"};
    std::vector<std::string> numButtons = {"[-]", "0", ".",
                                            "1", "2", "3",
                                            "4", "5", "6",
                                            "7", "8", "9",
                                            "C", "(", ")"
                                           };

    sf::RenderWindow& App;
    sf::Font font;
    sf::Mouse mouse;
};
