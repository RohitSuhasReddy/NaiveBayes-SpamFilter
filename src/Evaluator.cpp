#include "Evaluator.h"
#include <iostream>
#include <iomanip>

// TODO (P3): Full implementation

void Evaluator::evaluate(IClassifier& classifier, const std::vector<Document>& testDocs) {
    trueLabels_.clear();
    predLabels_.clear();
    confusion_.clear();

    for (const auto& doc : testDocs) {
        std::string pred = classifier.predict(doc);
        trueLabels_.push_back(doc.label);
        predLabels_.push_back(pred);
        confusion_[doc.label][pred]++;
    }
}

double Evaluator::accuracy() const {
    if (trueLabels_.empty()) return 0.0;
    int correct = 0;
    for (size_t i = 0; i < trueLabels_.size(); ++i) {
        if (trueLabels_[i] == predLabels_[i]) ++correct;
    }
    return static_cast<double>(correct) / trueLabels_.size();
}

std::map<std::string, double> Evaluator::precision() const {
    // TODO
    return {};
}

std::map<std::string, double> Evaluator::recall() const {
    // TODO
    return {};
}

std::map<std::string, double> Evaluator::f1() const {
    // TODO
    return {};
}

void Evaluator::printConfusionMatrix() const {
    // TODO: nice table
}

void Evaluator::printReport() const {
    std::cout << "Accuracy: " << std::fixed << std::setprecision(4) << accuracy() << "\n";
    // TODO: print per-class precision / recall / F1
}
