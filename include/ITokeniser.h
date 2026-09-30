#pragma once

#include <string>
#include <vector>

using namespace std;

class ITokeniser {
public:
    virtual ~ITokeniser() = default;
    virtual vector<string> tokenise(const string& text) const = 0;
};
