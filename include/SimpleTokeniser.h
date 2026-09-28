#pragma once

#include "ITokeniser.h"

/**
 * Basic tokenizer: lowercases, splits on whitespace/punctuation.
 */
class SimpleTokeniser : public ITokeniser {
public:
    std::vector<std::string> tokenize(const std::string& text) override;
};
