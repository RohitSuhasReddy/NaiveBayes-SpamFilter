#pragma once

#include <set>
#include <string>
#include <vector>
#include "Document.h"

/**
 * Global set of known words seen during training.
 */
class Vocabulary {
public:
    std::set<std::string> words;

    void add(const std::string& word);
    void buildFromDocuments(const std::vector<Document>& docs);
    bool contains(const std::string& word) const;
    size_t size() const;
};
