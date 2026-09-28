#pragma once

#include "ITokeniser.h"

/**
 * Optional: strips URLs, phone numbers, currency symbols, etc.
 * before basic tokenization.
 */
class RegexTokeniser : public ITokeniser {
public:
    std::vector<std::string> tokenize(const std::string& text) override;
};
