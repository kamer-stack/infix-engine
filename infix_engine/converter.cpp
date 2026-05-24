#include "converter.h"
#include "stack.h"
#include <stdexcept>

using namespace std;

// returns priority of operator
int priority(const string& op) {
    if (op == "*" || op == "/") return 2;
    if (op == "+" || op == "-") return 1;
    return 0;
}

// checks if opening and closing brackets match
bool bracketsMatch(const string& open, const string& close) {
    if (open == "(" && close == ")") return true;
    if (open == "[" && close == "]") return true;
    if (open == "{" && close == "}") return true;
    return false;
}

vector<Token> toPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    Stack<Token> opStack;
    // empty expression check
    if (tokens.empty())
        throw runtime_error("Logical error: empty expression");

    // expression cant start with * or /
    if (tokens[0].type == TokenType::OPERATOR && 
        (tokens[0].value == "*" || tokens[0].value == "/"))
        throw runtime_error("Syntax error: expression cant start with " + tokens[0].value);

    // expression cant end with any operator
    if (tokens.back().type == TokenType::OPERATOR)
        throw runtime_error("Syntax error: expression cant end with operator");

    // check for two operators in a row or two operands in a row
    for (int i = 1; i < tokens.size(); i++) {
        bool currIsOp = tokens[i].type == TokenType::OPERATOR;
        bool prevIsOp = tokens[i-1].type == TokenType::OPERATOR;
        bool currIsOperand = tokens[i].type == TokenType::NUMBER || tokens[i].type == TokenType::VARIABLE;
        bool prevIsOperand = tokens[i-1].type == TokenType::NUMBER || tokens[i-1].type == TokenType::VARIABLE;

        // two operators in a row (excluding unary minus)
        if (currIsOp && prevIsOp && tokens[i].value != "-")
            throw runtime_error("Syntax error: two operators in a row");

        // two operands in a row
        if (currIsOperand && prevIsOperand)
            throw runtime_error("Syntax error: missing operator between operands");
    }

    // empty brackets check
    for (int i = 0; i < tokens.size() - 1; i++) {
        if (tokens[i].type == TokenType::LPAREN && tokens[i+1].type == TokenType::RPAREN)
            throw runtime_error("Logical error: empty brackets");
    }

    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];

        // numbers and variables go straight to output
        if (t.type == TokenType::NUMBER || t.type == TokenType::VARIABLE) {
            output.push_back(t);
        }

        // operator
        else if (t.type == TokenType::OPERATOR) {

            // handle unary minus e.g -a or -(a+b)
            // its unary if its the first token or comes after an operator or opening bracket
            if (t.value == "-") {
                bool isUnary = (i == 0) ||
                               (tokens[i-1].type == TokenType::OPERATOR) ||
                               (tokens[i-1].type == TokenType::LPAREN);

                if (isUnary) {
                    // treat as "0 - " so postfix evaluation works normally
                    output.push_back({TokenType::NUMBER, "0"});
                }
            }

            // pop operators with higher or equal priority to output first
            while (!opStack.isEmpty() &&
                   opStack.top().type == TokenType::OPERATOR &&
                   priority(opStack.top().value) >= priority(t.value)) {
                output.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(t);
        }

        // opening bracket always goes to stack
        else if (t.type == TokenType::LPAREN) {
            opStack.push(t);
        }

        // closing bracket
        else if (t.type == TokenType::RPAREN) {
            // pop until we find the matching opening bracket
            bool matched = false;
            while (!opStack.isEmpty()) {
                if (opStack.top().type == TokenType::LPAREN) {
                    // check if brackets actually match e.g (a] is wrong
                    if (!bracketsMatch(opStack.top().value, t.value))
                        throw runtime_error("Syntax error: mismatched brackets");
                    opStack.pop(); // discard the opening bracket
                    matched = true;
                    break;
                }
                output.push_back(opStack.top());
                opStack.pop();
            }

            if (!matched)
                throw runtime_error("Syntax error: extra closing bracket");
        }
    }

    // pop whatever is left in stack
    while (!opStack.isEmpty()) {
        if (opStack.top().type == TokenType::LPAREN)
            throw runtime_error("Syntax error: unclosed bracket");
        output.push_back(opStack.top());
        opStack.pop();
    }

    return output;
}