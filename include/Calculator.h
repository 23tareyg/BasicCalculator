#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <queue>
#include <stack>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "Constants.h"

enum class TokenType {
    NUMBER,
    FUNCTION,
    OPERATOR,
    NUM_TOKENS
};

enum class dispMode {
    CLEAR,
    ANSWER,
    EXPR,
    NUM_MODES
};


class Token {
public:
    Token() = delete;
    Token(std::string s, TokenType t) : tokenContent(s), type(t) {}
    Token(char s, TokenType t) : type(t) {
        tokenContent.push_back(s);
    }
private:
    std::string tokenContent;
    TokenType type;

friend class Calculator;
};

class Calculator {
public:
    Calculator() = delete;
    Calculator(std::string s, sf::RenderWindow& w, sf::Mouse m) : expression(s), window(w), mouse(m) {}
    Calculator(sf::RenderWindow& w, sf::Mouse m) : window(w), mouse(m) {}

    std::string loadExpression();
    void deleteSpaces();
    void tokenize();
    void shuntingYard();
    void evaluatePostfix();
    void run();

    std::string getMouseNum(sf::Vector2i mousePos);
    void handlePress(sf::RenderWindow& App);

private:
    std::string expression;
    std::vector<Token> tokens;
    std::queue<Token> outputQ;
    double ans = 0;

    std::vector<char> operators = { '(', ')', '^', '+', '-', '*', '/' };
    std::vector<std::string> functions = { "sin", "cos", "tan" };

    sf::RenderWindow& window;
    sf::Mouse mouse;
    sf::Font font;

friend class DrawCalculator;
};

int getOpPrecedence(char c);
void drawStandText(sf::Text& text, sf::Font& font, sf::Color color, int size, std::string content);
