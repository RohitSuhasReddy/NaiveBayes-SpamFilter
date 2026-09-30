#pragma once

#include <string>
#include <map>
#include "ITokeniser.h"

using namespace std;

class Document {
public:
    string text;
    string label;
    map<string, int> wordCount;

    void buildWordCount(const ITokeniser& tokeniser);
};
