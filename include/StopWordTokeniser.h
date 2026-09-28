#pragma once

#include "ITokeniser.h"
#include <set>
#include <string>

/**
 * Removes common English stop words after basic tokenization.
 */
class StopWordTokeniser : public ITokeniser {
public:
    StopWordTokeniser();
    std::vector<std::string> tokenize(const std::string& text) override;

private:
    std::set<std::string> stopWords;
};
