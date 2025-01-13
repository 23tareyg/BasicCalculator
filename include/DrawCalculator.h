#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Calculator.h"
#include "Constants.h"

using namespace CalculatorConst;

class DrawCalculator {
public:
    DrawCalculator(int hnx, int hny, int hox, int hoy, int hfx, int hfy, sf::RenderWindow& a) : 
        heightNumX(hnx), heightNumY(hny), heightOperatorsX(hnx), heightOperatorsY(hny),
        heightFunctionsX(hfx), heightFunctionsY(hfy), App(a) {}
    DrawCalculator(sf::RenderWindow& a) : App(a) {
        int heightNumX = NUM_WIDTH;
        int heightNumY = NUM_HEIGHT;
        int heightOperatorsX = OP_WIDTH;
        int heightOperatorsY = OP_HEIGHT;
        int heightFunctionsX = FUNC_WIDTH;
        int heightFunctionsY = FUNC_HEIGHT;
    }
    DrawCalculator() = default;

    void drawNumpad();
    void drawOperators();
    void drawClear();
    void drawFuncs();
    void drawAll();

private:
    // all refer to height of a single "button"
    int heightNumX = 130;
    int heightNumY = 130;
    int heightOperatorsX = 210;
    int heightOperatorsY = 130;
    int heightFunctionsX = 200;
    int heightFunctionsY = 130;

    sf::RenderWindow& App;
};