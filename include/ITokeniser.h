#pragma once

#include <string>
#include <vector>

/**
 * Interface for all tokenizers (Strategy / inheritance showcase).
 */
class ITokeniser {
public:
    virtual ~ITokeniser() = default;

    // Tokenize a raw message into a list of tokens
    virtual std::vector<std::string> tokenize(const std::string& text) = 0;
};
