// to run:
//g++ converter.cpp tokenizer.cpp evaluator.cpp main.cpp -o program
// then run ./program and input an expression like (a+b)*c
#include <iostream>
#include <map>
#include <set>
#include "tokenizer.h"
#include "converter.h"
#include "evaluator.h"

using namespace std;

int main() {
    string expr;
    getline(cin, expr);

    try {
        // stage 1 - tokenize
        vector<Token> tokens = tokenize(expr);

        // stage 2 - convert to postfix
        vector<Token> postfix = toPostfix(tokens);

        // print postfix to stdout
        for (auto& t : postfix)
            cout << t.value << " ";
        cout << "\n";

        // collect all variables from postfix
        set<string> vars;
        for (auto& t : postfix)
            if (t.type == TokenType::VARIABLE)
                vars.insert(t.value);

        // ask user for each variable value (stderr)
        map<string, double> values;
        for (auto& v : vars) {
            cerr << "Enter value for " << v << ": ";
            double val;
            cin >> val;
            values[v] = val;
        }

        // stage 3 - evaluate
        double result = evaluate(postfix, values);

        // final result to stdout only
        cout << result << "\n";

    } catch (runtime_error& e) {
        string msg = e.what();

        if (msg.find("Syntax") != string::npos) {
            cerr << msg << "\n";
            return 1;
        } else if (msg.find("Runtime") != string::npos) {
            cerr << msg << "\n";
            return 2;
        } else if (msg.find("Logical") != string::npos) {
            cerr << msg << "\n";
            return 3;
        }

        // unknown error
        cerr << msg << "\n";
        return 1;
    }

    return 0;
}