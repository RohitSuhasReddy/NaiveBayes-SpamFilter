#pragma once

#include <string>
#include <vector>
#include <map>
#include "Document.h"
#include "Vocabulary.h"
#include "IClassifier.h"

/**
 * Multinomial Naive Bayes classifier for 3 classes: Ham / Spam / Scam.
 * Uses Laplace (add-one) smoothing.
 */
class NaiveBayesClassifier : public IClassifier {
public:
    void train(const std::vector<Document>& documents) override;
    std::string predict(const Document& doc) override;

    // Optional: return class probabilities (for display)
    std::map<std::string, double> predictProba(const Document& doc);

private:
    Vocabulary vocab_;
    std::map<std::string, int> classCounts_;               // class -> number of docs
    std::map<std::string, int> classTotalWords_;           // class -> total word occurrences
    std::map<std::string, std::map<std::string, int>> wordCounts_; // class -> (word -> count)

    double logPrior(const std::string& classLabel) const;
    double logLikelihood(const std::string& word, const std::string& classLabel) const;
};
