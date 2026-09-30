#pragma once

#include <string>
#include <vector>
#include <map>
#include "Document.h"
#include "Vocabulary.h"

using namespace std;

/**
 * Multinomial Naive Bayes for 3 classes: Ham / Spam / Scam.
 * Uses Laplace (add-one) smoothing.
 */
class NaiveBayesClassifier {
public:
    void train(const vector<Document>& documents);
    string predict(const Document& doc) const;
    map<string, double> predictScores(const Document& doc) const;

    bool isTrained() const { return trained_; }

private:
    bool trained_ = false;

    Vocabulary vocab_;

    map<string, int> classDocCounts_;
    map<string, int> classTotalWords_;
    map<string, map<string, int>> wordCounts_;

    int totalDocs_ = 0;

    double logPrior(const string& classLabel) const;
    double logLikelihood(const string& word, const string& classLabel) const;
};