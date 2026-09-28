#include "NGramTokeniser.h"
#include "SimpleTokeniser.h"

NGramTokeniser::NGramTokeniser(int n) : n_(n) {}

std::vector<std::string> NGramTokeniser::tokenize(const std::string& text) {
    SimpleTokeniser basic;
    auto unigrams = basic.tokenize(text);

    if (n_ <= 1) return unigrams;

    std::vector<std::string> ngrams;
    for (size_t i = 0; i + n_ <= unigrams.size(); ++i) {
        std::string gram = unigrams[i];
        for (int k = 1; k < n_; ++k) {
            gram += "_" + unigrams[i + k];
        }
        ngrams.push_back(gram);
    }
    return ngrams;
}
