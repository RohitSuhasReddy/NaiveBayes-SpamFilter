#pragma once

#include <bits/stdc++.h>
#include "Document.h"
#include "Vocabulary.h"

using namespace std;


class NaiveBayesClassifier {
public:
    // Learn counts from labeled training documents (each has label + wordCount).
    void train(const vector<Document>& documents);

    // Return the most likely class label for one document.
    string predict(const Document& doc) const;

    // Log-score per class (higher = more likely). Useful for debugging / CLI.
    map<string, double> predictScores(const Document& doc) const;

    // True after train() has been called successfully.
    bool isTrained() const { return trained_; }

private:
    bool trained_ = false;

    Vocabulary vocab_;  // all unique words seen during training (|V|)

    map<string, int> classDocCounts_;   // class -> number of training docs
    map<string, int> classTotalWords_;  // class -> total word occurrences
    map<string, map<string, int>> wordCounts_;  // class -> (word -> count)

    int totalDocs_ = 0;  // total training documents

    // log P(class) = log(count(class) / totalDocs)
    double logPrior(const string& classLabel) const;

    // log P(word | class) with Laplace: log( (count+1) / (totalWords + |V|) )
    double logLikelihood(const string& word, const string& classLabel) const;
};
