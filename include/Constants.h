#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace CalculatorConst {
    constexpr int SCREEN_WIDTH = 600;
    constexpr int SCREEN_HEIGHT = 1000;
    constexpr int NUM_WIDTH = 130;
    constexpr int NUM_HEIGHT = 130;
    constexpr int OP_WIDTH = 210;
    constexpr int OP_HEIGHT = 130;
    constexpr int FUNC_WIDTH = 200;
    constexpr int FUNC_HEIGHT = 130;

    const sf::Color textCol(0, 0, 0);
    const sf::Color outlineCol(183, 183, 183);
    const sf::Color numBackgroundCol(255, 255, 255);
    const sf::Color opBackgroundCol(205, 205, 205);
};

#endif