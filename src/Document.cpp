#include "Document.h"

using namespace std;

void Document::buildWordCount(const ITokeniser& tokeniser) {
    wordCount.clear();
    for (const auto& word : tokeniser.tokenise(text)) {
        wordCount[word]++;
    }
}
