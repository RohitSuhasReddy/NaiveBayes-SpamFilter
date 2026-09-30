#include "StopWordTokeniser.h"

using namespace std;

StopWordTokeniser::StopWordTokeniser() {
    const char* words[] = {
        "a", "an", "the", "and", "or", "but", "if", "then", "else",
        "is", "am", "are", "was", "were", "be", "been", "being",
        "to", "of", "in", "on", "at", "for", "from", "by", "with",
        "as", "it", "its", "this", "that", "these", "those",
        "i", "me", "my", "we", "our", "you", "your", "u", "ur",
        "he", "she", "they", "them", "his", "her", "their",
        "do", "does", "did", "have", "has", "had",
        "not", "no", "so", "too", "very", "just", "can", "will",
        "about", "into", "over", "after", "before", "up", "down",
        "out", "off", "again", "once", "here", "there", "when",
        "where", "why", "how", "all", "any", "both", "each",
        "few", "more", "most", "other", "some", "such", "than",
        "also", "only"
    };

    for (const char* w : words) {
        stopWords_.insert(w);
    }
}

vector<string> StopWordTokeniser::tokenise(const string& text) const {
    vector<string> tokens;
    for (const auto& word : inner_.tokenise(text)) {
        if (stopWords_.find(word) == stopWords_.end()) {
            tokens.push_back(word);
        }
    }
    return tokens;
}
