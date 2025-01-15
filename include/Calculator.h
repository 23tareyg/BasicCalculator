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
    ERR,
    NUM_MODES
};

// Token class handles the tokens that go into the parser, which are strings of variable length
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

// Calculator class handles the computation of the expression by tokenizing, performing the Shunting Yard algorithm, and
// evaluating the tokens in postfix notation. The run() function performs all the functionality of the other functions 
// in the correct order.
class Calculator {
public:
    Calculator() {}

    void run();

    std::string expression;
    std::string dispExpression;

private:
    std::string loadExpression();
    void deleteSpaces();
    void tokenize();
    void shuntingYard();
    void evaluatePostfix();
    void clear();
    std::string getMouseNum(sf::Vector2i mousePos);
    void handlePress(sf::RenderWindow& App);
    
    std::vector<Token> tokens;
    std::queue<Token> outputQ;
    double ans = 0;
    std::vector<char> operators = { '(', ')', '^', '+', '-', '*', '/' };
    std::vector<std::string> functions = { "sin", "cos", "tan", "neg"};

friend class DrawCalculator;
};

// Helper functions
int getOpPrecedence(char c);
void drawStandText(sf::Text& text, sf::Font& font, sf::Color color, int size, std::string content);
double negative(double n);
std::string tokenTypeString(TokenType t);


