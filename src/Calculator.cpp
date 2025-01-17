#include "../include/Calculator.h"

using namespace CalculatorConst;

// Helper variables
std::string temp, tempfunc;

std::string Calculator::loadExpression() {
    return expression;
}

// Only necessary for command line input
void Calculator::deleteSpaces() {
    for (auto i = expression.begin(); i != expression.end(); i++) {
        if (*i == ' ') expression.erase(i);
    }
}

// Take string and convert to vector of Tokens
void Calculator::tokenize() {
    for (auto c = expression.begin(); c != expression.end(); c++) {
        // check for numbers
        if (std::isdigit(*c) || *c == '.') {
            temp.push_back(*c);
            bool nextIsDigit = std::isdigit(*(c+1)) || *(c+1) == '.';
            if ((c+1) == expression.end() || !nextIsDigit) {
                Token t(temp, TokenType::NUMBER);
                tokens.push_back(t);
                temp.clear();
            }
        }
        
        // check for operators
        else if (std::find(operators.begin(), operators.end(), *c) != operators.end()) {
            Token t(*c, TokenType::OPERATOR);
            tokens.push_back(t);
        }

        // check for functions
        else if (std::isalpha(*c)) {
            tempfunc.push_back(*c);
            bool nextIsLet = std::isalpha(*(c+1));
            if ((c+1) == expression.end() || !nextIsLet) {
                if(std::find(functions.begin(), functions.end(), tempfunc) != functions.end()) {
                    Token t(tempfunc, TokenType::FUNCTION);
                    tokens.push_back(t);
                    tempfunc.clear();
                } else {
                    std::__throw_invalid_argument("Invalid Expression");
                }
            }
        }

        else {
            std::__throw_invalid_argument("Invalid Expression");
        }
    }
    std::cout << "TOKENS:" << std::endl;
    for (Token i : tokens) std::cout << i.tokenContent << " " << tokenTypeString(i.type) << std::endl;
    std::cout << "END TOKENS" << std::endl;
}

// Take vector of Tokens and convert to postfix
void Calculator::shuntingYard() {
    std::stack<Token> opStack;

    if (tokens[0].type == TokenType::OPERATOR) throw std::__throw_logic_error;
    for (auto i : tokens) {
        if (i.type == TokenType::NUMBER) {
            outputQ.push(i);
        } else if (i.type == TokenType::FUNCTION) {
            opStack.push(i);
        } else if (i.type == TokenType::OPERATOR && i.tokenContent[0] != '(' && i.tokenContent[0] != ')') {
            while (!opStack.empty() && opStack.top().tokenContent != "(" && 
                (getOpPrecedence(opStack.top().tokenContent[0]) > getOpPrecedence(i.tokenContent[0]) || opStack.top().tokenContent[0] == 'n' ||
                    (getOpPrecedence(opStack.top().tokenContent[0]) == getOpPrecedence(i.tokenContent[0]) && i.tokenContent[0] != '^')
                )
            ) 
            {
                outputQ.push(opStack.top());
                opStack.pop();
            }
            opStack.push(i);
        } else if (i.tokenContent[0] == '(') {
            opStack.push(i);
        } else if (i.tokenContent[0] == ')') {
            if (opStack.empty() || opStack.top().tokenContent[0] == '(' && outputQ.empty()) throw std::__throw_logic_error;
            while (opStack.top().tokenContent[0] != '(') {
                if (opStack.empty()) throw std::__throw_logic_error;
                outputQ.push(opStack.top());
                opStack.pop();
            }
            if(opStack.top().tokenContent[0] != '(') throw std::__throw_logic_error;
            opStack.pop();
            if (!opStack.empty() && opStack.top().type == TokenType::FUNCTION) {
                Token buf = opStack.top();
                opStack.pop();
                outputQ.push(buf);
            }
        }
    }

    while (!opStack.empty()) {
        if (opStack.top().tokenContent[0] == '(' || opStack.top().tokenContent[0] == ')') throw std::__throw_logic_error;
        Token buf = opStack.top();
        opStack.pop();
        outputQ.push(buf);
    }
}

// Evaluate postfix Tokens and store in variable ans
void Calculator::evaluatePostfix() {
    std::stack<double> vals;

    while(!outputQ.empty()) {
        Token tok = outputQ.front();
        outputQ.pop();

        if (tok.type == TokenType::NUMBER) {
            vals.push(std::stod(tok.tokenContent));
        } else if (tok.type == TokenType::OPERATOR) {
            if (vals.empty()) throw std::__throw_logic_error;
            double opB = vals.top();
            vals.pop();
            if (vals.empty()) throw std::__throw_logic_error;
            double opA = vals.top();
            vals.pop();

            switch (tok.tokenContent[0]) {
                case '+': vals.push(opA + opB); break;
                case '-': vals.push(opA - opB); break;
                case '*': vals.push(opA * opB); break;
                case '/': vals.push(opA / opB); break;
                case '^': vals.push(std::pow(opA, opB)); break;
            }
        } else if (tok.type == TokenType::FUNCTION) {
            double op = vals.top();
            vals.pop();

            if (tok.tokenContent == "sin") vals.push(sin(op));
            else if (tok.tokenContent == "cos") vals.push(cos(op));
            else if (tok.tokenContent == "tan") vals.push(tan(op));
            else if (tok.tokenContent == "neg") vals.push(negative(op));
            else throw std::__throw_invalid_argument;
        }
    }

    if (vals.empty()) throw std::__throw_logic_error;
    ans = vals.top();
}

// Run all necessary functions
void Calculator::run() {
    deleteSpaces();
    tokenize();
    shuntingYard();
    evaluatePostfix();
    std::cout << "Answer: " << ans << std::endl;
}

// Clear all stacks, queues, and strings
void Calculator::clear() {
    expression.clear();
    dispExpression.clear();
    tokens.clear();
    while (!outputQ.empty()) outputQ.pop();
}

std::string Calculator::getMouseNum(sf::Vector2i mousePos) {
    if (mousePos.y > 1000 - ((NUM_HEIGHT*4) + OP_HEIGHT + FUNC_HEIGHT) && 
        mousePos.y <= 1000 - ((NUM_HEIGHT*4) + OP_HEIGHT) )
    {
        // mouse is at top row
        if (mousePos.x > 0 && mousePos.x <= FUNC_WIDTH) return "sin(";
        else if (mousePos.x > FUNC_WIDTH && mousePos.x <= FUNC_WIDTH*2) return "cos(";
        else if (mousePos.x > FUNC_WIDTH*2 && mousePos.x <= FUNC_WIDTH*3) return "tan(";
        else return "";
    } 
    else if (mousePos.y > 1000 - ((NUM_HEIGHT*4) + OP_HEIGHT) && 
                mousePos.y <= 1000 - (NUM_HEIGHT*4)) 
    {
        // mouse is at second row from top
        if (mousePos.x > 0 && mousePos.x <= NUM_WIDTH) return "CLEAR";
        else if (mousePos.x > NUM_WIDTH && mousePos.x <= NUM_WIDTH*2) return "(";
        else if (mousePos.x > NUM_WIDTH*2 && mousePos.x <= NUM_WIDTH*3) return ")";
        else if (mousePos.x <= SCREEN_WIDTH) return "/";
        else return "";
    }
    else if (mousePos.y > 1000 - (NUM_HEIGHT*4) && 
                mousePos.y <= 1000 - (NUM_HEIGHT*3)) 
    {
        // mouse is at third row from top
        if (mousePos.x > 0 && mousePos.x <= NUM_WIDTH) return "7";
        else if (mousePos.x > NUM_WIDTH && mousePos.x <= NUM_WIDTH*2) return "8";
        else if (mousePos.x > NUM_WIDTH*2 && mousePos.x <= NUM_WIDTH*3) return "9";
        else if (mousePos.x > NUM_WIDTH*3 && mousePos.x <= SCREEN_WIDTH) return "*";
        else return "";
    }
    else if (mousePos.y > 1000 - (NUM_HEIGHT*3) && 
                mousePos.y <= 1000 - (NUM_HEIGHT*2)) 
    {
        // mouse is at fourth row from top
        if (mousePos.x > 0 && mousePos.x <= NUM_WIDTH) return "4";
        else if (mousePos.x > NUM_WIDTH && mousePos.x <= NUM_WIDTH*2) return "5";
        else if (mousePos.x > NUM_WIDTH*2 && mousePos.x <= NUM_WIDTH*3) return "6";
        else if (mousePos.x > NUM_WIDTH*3 && mousePos.x <= SCREEN_WIDTH) return "-";
        else return "";
    }
    else if (mousePos.y > 1000 - (NUM_HEIGHT*2) && 
                mousePos.y <= 1000 - (NUM_HEIGHT)) 
    {
        // mouse is at fifth row from top
        if (mousePos.x > 0 && mousePos.x <= NUM_WIDTH) return "1";
        else if (mousePos.x > NUM_WIDTH && mousePos.x <= NUM_WIDTH*2) return "2";
        else if (mousePos.x > NUM_WIDTH*2 && mousePos.x <= NUM_WIDTH*3) return "3";
        else if (mousePos.x > NUM_WIDTH*3 && mousePos.x <= SCREEN_WIDTH) return "+";
        else return "";
    }
    else if (mousePos.y > 1000 - ((NUM_HEIGHT)) && 
                mousePos.y <= 1000) 
    {
        // mouse is at sixth row from top
        if (mousePos.x > 0 && mousePos.x <= NUM_WIDTH) return "neg";
        else if (mousePos.x > NUM_WIDTH && mousePos.x <= NUM_WIDTH*2) return "0";
        else if (mousePos.x > NUM_WIDTH*2 && mousePos.x <= NUM_WIDTH*3) return ".";
        else if (mousePos.x > NUM_WIDTH*3 && mousePos.x <= SCREEN_WIDTH) return "ENTER";
        else return "";
    }
    else return "";
}

int getOpPrecedence(char c) {
    switch (c) {
        case '^' || 'n':
            return 4;
            break;
        case '*':
        case '/':
            return 3;
            break;
        case '+':
        case '-':
            return 2;
            break;
        default:
            return 0;
            break;
    }
    return 0;
}

void drawStandText(sf::Text& text, sf::Font& font, sf::Color color, int size, std::string content) {
    text.setFont(font);
    text.setFillColor(color);
    text.setCharacterSize(size);
    text.setString(content);
}

double negative(double n) {
    return n * (-1);
}

std::string tokenTypeString(TokenType t) {
    switch (t) {
        case TokenType::FUNCTION: 
            return "function";
            break;
        case TokenType::NUMBER:
            return "number";
            break;
        case TokenType::OPERATOR: 
            return "operator";
            break;
        default: return "";
    }
}