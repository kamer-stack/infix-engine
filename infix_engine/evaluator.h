#pragma once
#include "tokenizer.h"
#include <vector>
#include <map>

using namespace std;

double evaluate(const vector<Token>& postfix, const map<string, double>& values);