#include "RegexTokeniser.h"
#include "SimpleTokeniser.h"
#include <regex>

std::vector<std::string> RegexTokeniser::tokenize(const std::string& text) {
    // Remove URLs, emails, phone-like numbers, currency symbols
    std::string cleaned = text;

    // URLs
    cleaned = std::regex_replace(cleaned, std::regex(R"((https?://|www\.)\S+)", std::regex::icase), " ");
    // Emails
    cleaned = std::regex_replace(cleaned, std::regex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)"), " ");
    // Phone-like sequences
    cleaned = std::regex_replace(cleaned, std::regex(R"(\b\d{3}[-.\s]?\d{3}[-.\s]?\d{4}\b)"), " ");
    // Currency symbols + numbers
    cleaned = std::regex_replace(cleaned, std::regex(R"([$€£¥]\s*\d+[\d,.]*)"), " ");

    SimpleTokeniser basic;
    return basic.tokenize(cleaned);
}
