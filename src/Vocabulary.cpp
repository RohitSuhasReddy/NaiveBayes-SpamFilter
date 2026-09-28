#include "Vocabulary.h"

void Vocabulary::add(const std::string& word) {
    words.insert(word);
}

void Vocabulary::buildFromDocuments(const std::vector<Document>& docs) {
    for (const auto& doc : docs) {
        for (const auto& pair : doc.wordCount) {
            words.insert(pair.first);
        }
    }
}

bool Vocabulary::contains(const std::string& word) const {
    return words.find(word) != words.end();
}

size_t Vocabulary::size() const {
    return words.size();
}
