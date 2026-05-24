#include "evaluator.h"
#include "stack.h"
#include <stdexcept>

using namespace std;

double evaluate(const vector<Token>& postfix, const map<string, double>& values) {
    Stack<double> numStack;

    for (auto& t : postfix) {

        // if number just push it
        if (t.type == TokenType::NUMBER) {
            numStack.push(stod(t.value));
        }

        // if variable look up its value
        else if (t.type == TokenType::VARIABLE) {
            if (values.find(t.value) == values.end())
                throw runtime_error("Runtime error: variable '" + t.value + "' has no value");
            numStack.push(values.at(t.value));
        }

        // if operator pop 2 values and apply it
        else if (t.type == TokenType::OPERATOR) {
            if (numStack.size() < 2)
                throw runtime_error("Logical error: not enough operands");

            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();

            if (t.value == "+") numStack.push(a + b);
            else if (t.value == "-") numStack.push(a - b);
            else if (t.value == "*") numStack.push(a * b);
            else if (t.value == "/") {
                if (b == 0)
                    throw runtime_error("Runtime error: division by zero");
                numStack.push(a / b);
            }
        }
    }

    // at end stack should have exactly 1 value
    if (numStack.size() != 1)
        throw runtime_error("Logical error: invalid expression");

    return numStack.top();
}