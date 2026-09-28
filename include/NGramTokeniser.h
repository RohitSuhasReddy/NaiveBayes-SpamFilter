#pragma once

#include "ITokeniser.h"

/**
 * Optional: produces n-grams (e.g. bigrams) instead of single words.
 */
class NGramTokeniser : public ITokeniser {
public:
    explicit NGramTokeniser(int n = 2);
    std::vector<std::string> tokenize(const std::string& text) override;

private:
    int n_;
};
