#include "NaiveBayesClassifier.h"
#include <cmath>
#include <limits>

// TODO (P1): Full implementation

void NaiveBayesClassifier::train(const std::vector<Document>& documents) {
    // 1. Count documents per class
    // 2. Count word occurrences per class
    // 3. Build vocabulary
    // 4. Store totals for Laplace smoothing
    (void)documents; // suppress unused warning until implemented
}

std::string NaiveBayesClassifier::predict(const Document& doc) {
    // For each class compute log P(class) + sum log P(word|class)
    // Return class with highest score
    (void)doc;
    return "Ham"; // placeholder
}

std::map<std::string, double> NaiveBayesClassifier::predictProba(const Document& doc) {
    (void)doc;
    return {};
}

double NaiveBayesClassifier::logPrior(const std::string& classLabel) const {
    (void)classLabel;
    return 0.0;
}

double NaiveBayesClassifier::logLikelihood(const std::string& word, const std::string& classLabel) const {
    (void)word;
    (void)classLabel;
    return 0.0;
}
