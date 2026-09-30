#pragma once

#include "ITokeniser.h"

using namespace std;

class SimpleTokeniser : public ITokeniser {
public:
    vector<string> tokenise(const string& text) const override;
};
