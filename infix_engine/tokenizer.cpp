#include "tokenizer.h"
#include <stdexcept>
#include <cctype>

using namespace std;

vector<Token> tokenize(const string& expr) {
    vector<Token> tokens;
    int i = 0;

    while (i < expr.size()) {

        // skip spaces
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        // number
        if (isdigit(expr[i])) {
            string num = "";
            while (i < expr.size() && isdigit(expr[i]))
                num += expr[i++];

            // like 2abc is not valid
            if (i < expr.size() && (isalpha(expr[i]) || expr[i] == '_'))
                throw runtime_error("Syntax error: invalid token '" + num + "'");

            tokens.push_back({TokenType::NUMBER, num});
            continue;
        }

        // variable name (must start with letter or underscore)
        if (isalpha(expr[i]) || expr[i] == '_') {
            string var = "";
            while (i < expr.size() && (isalnum(expr[i]) || expr[i] == '_'))
                var += expr[i++];
            tokens.push_back({TokenType::VARIABLE, var});
            continue;
        }

        // operators
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            tokens.push_back({TokenType::OPERATOR, string(1, expr[i])});
            i++;
            continue;
        }

        // opening brackets
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            tokens.push_back({TokenType::LPAREN, string(1, expr[i])});
            i++;
            continue;
        }

        // closing brackets
        if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            tokens.push_back({TokenType::RPAREN, string(1, expr[i])});
            i++;
            continue;
        }

        // anything else is invalid
        throw runtime_error(string("Syntax error: unexpected character '") + expr[i] + "'");
    }

    return tokens;
}