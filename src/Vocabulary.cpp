#include "Vocabulary.h"

using namespace std;

void Vocabulary::add(const string& word) {
    words_.insert(word);
}

bool Vocabulary::contains(const string& word) const {
    return words_.find(word) != words_.end();
}

size_t Vocabulary::size() const {
    return words_.size();
}
