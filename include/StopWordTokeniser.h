#pragma once

#include "ITokeniser.h"
#include "SimpleTokeniser.h"
#include <unordered_set>

using namespace std;

class StopWordTokeniser : public ITokeniser {
public:
    StopWordTokeniser();
    vector<string> tokenise(const string& text) const override;

private:
    SimpleTokeniser inner_;
    unordered_set<string> stopWords_;
};
