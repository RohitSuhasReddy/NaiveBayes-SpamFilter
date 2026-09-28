#include "StopWordTokeniser.h"
#include "SimpleTokeniser.h"

StopWordTokeniser::StopWordTokeniser() {
    // Minimal English stop-word list – expand as needed
    const char* stops[] = {
        "a", "an", "the", "and", "or", "but", "in", "on", "at", "to", "for",
        "of", "is", "are", "was", "were", "be", "been", "being", "have", "has",
        "had", "do", "does", "did", "will", "would", "could", "should", "may",
        "might", "must", "shall", "can", "need", "dare", "ought", "used",
        "i", "you", "he", "she", "it", "we", "they", "me", "him", "her", "us",
        "them", "my", "your", "his", "its", "our", "their", "this", "that",
        "these", "those", "am", "is", "are", "was", "were", "be", "been"
    };
    for (const char* s : stops) {
        stopWords.insert(s);
    }
}

std::vector<std::string> StopWordTokeniser::tokenize(const std::string& text) {
    SimpleTokeniser basic;
    auto tokens = basic.tokenize(text);

    std::vector<std::string> filtered;
    for (const auto& t : tokens) {
        if (stopWords.find(t) == stopWords.end()) {
            filtered.push_back(t);
        }
    }
    return filtered;
}
