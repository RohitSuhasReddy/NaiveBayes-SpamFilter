#pragma once

#include <string>
#include <vector>
#include <map>
#include "Document.h"
#include "IClassifier.h"

/**
 * Evaluation metrics: accuracy, precision, recall, F1, confusion matrix.
 */
class Evaluator {
public:
    // Run predictions on a test set and store results
    void evaluate(IClassifier& classifier, const std::vector<Document>& testDocs);

    double accuracy() const;
    std::map<std::string, double> precision() const;   // per class
    std::map<std::string, double> recall() const;      // per class
    std::map<std::string, double> f1() const;          // per class

    void printConfusionMatrix() const;
    void printReport() const;

private:
    std::vector<std::string> trueLabels_;
    std::vector<std::string> predLabels_;
    std::map<std::string, std::map<std::string, int>> confusion_; // true -> pred -> count
};
