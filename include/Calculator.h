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

#include <SFML/Graphics.hpp>

#include "Constants.h"

enum class TokenType {
    NUMBER,
    FUNCTION,
    OPERATOR,
    NUM_TOKENS
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
    void handlePress();

private:
    std::string expression;
    std::vector<Token> tokens;
    std::queue<Token> outputQ;
    double ans = 0;

    std::vector<char> operators = { '(', ')', '^', '+', '-', '*', '/' };
    std::vector<std::string> functions = { "sin", "cos", "tan" };

    sf::RenderWindow& window;
    sf::Mouse mouse;

friend class DrawCalculator;
};

int getOpPrecedence(char c);