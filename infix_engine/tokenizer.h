#pragma once
#include <string>
#include <vector>
using namespace std;

// token types i need
enum class TokenType {
    NUMBER,
    VARIABLE,
    OPERATOR,
    LPAREN,
    RPAREN
};

struct Token {
    TokenType type;
    string value;
};

vector<Token> tokenize(const string& input);