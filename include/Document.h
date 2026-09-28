#pragma once

#include <string>
#include <map>

/**
 * Represents one SMS message.
 * Holds the raw text, its class label, and the word frequency map.
 */
class Document {
public:
    std::string text;
    std::string label;                      // "Ham", "Spam", or "Scam"
    std::map<std::string, int> wordCount;   // word -> count

    Document() = default;
    Document(const std::string& t, const std::string& l);

    // Optional helpers
    void setText(const std::string& t);
    void setLabel(const std::string& l);
};
