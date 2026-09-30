#include "Evaluator.h"
#include <iomanip>
#include <stdexcept>

using namespace std;

const vector<string> Evaluator::kLabels = {"Ham", "Spam", "Scam"};

double Evaluator::safeDivide(double numerator, double denominator) {
    if (denominator == 0.0) {
        return 0.0;
    }
    return numerator / denominator;
}

Evaluator::Metrics Evaluator::evaluate(const vector<string>& yTrue,
                                       const vector<string>& yPred) const {
    if (yTrue.size() != yPred.size()) {
        throw invalid_argument("yTrue and yPred must have the same length");
    }

    Metrics m;
    m.total = static_cast<int>(yTrue.size());

    for (const auto& label : kLabels) {
        m.precision[label] = 0.0;
        m.recall[label] = 0.0;
        m.f1[label] = 0.0;
        for (const auto& pred : kLabels) {
            m.confusion[label][pred] = 0;
        }
    }

    for (size_t i = 0; i < yTrue.size(); ++i) {
        const string& actual = yTrue[i];
        const string& predicted = yPred[i];
        m.confusion[actual][predicted]++;
        if (actual == predicted) {
            m.correct++;
        }
    }

    m.accuracy = safeDivide(static_cast<double>(m.correct), m.total);

    double sumP = 0.0;
    double sumR = 0.0;
    double sumF1 = 0.0;

    for (const auto& label : kLabels) {
        int tp = m.confusion[label][label];
        int fp = 0;
        int fn = 0;

        for (const auto& other : kLabels) {
            if (other == label) {
                continue;
            }
            fp += m.confusion[other][label];
            fn += m.confusion[label][other];
        }

        double p = safeDivide(static_cast<double>(tp), tp + fp);
        double r = safeDivide(static_cast<double>(tp), tp + fn);
        double f1 = safeDivide(2.0 * p * r, p + r);

        m.precision[label] = p;
        m.recall[label] = r;
        m.f1[label] = f1;

        sumP += p;
        sumR += r;
        sumF1 += f1;
    }

    const double nClasses = static_cast<double>(kLabels.size());
    m.macroPrecision = sumP / nClasses;
    m.macroRecall = sumR / nClasses;
    m.macroF1 = sumF1 / nClasses;

    return m;
}

void Evaluator::printConfusionMatrix(const Metrics& metrics, ostream& out) const {
    const int cellW = 10;

    out << "Confusion matrix (rows = true, columns = predicted)\n";
    out << setw(cellW) << " ";
    for (const auto& pred : kLabels) {
        out << setw(cellW) << pred;
    }
    out << "\n";

    for (const auto& actual : kLabels) {
        out << setw(cellW) << actual;
        for (const auto& pred : kLabels) {
            int count = 0;
            auto rowIt = metrics.confusion.find(actual);
            if (rowIt != metrics.confusion.end()) {
                auto colIt = rowIt->second.find(pred);
                if (colIt != rowIt->second.end()) {
                    count = colIt->second;
                }
            }
            out << setw(cellW) << count;
        }
        out << "\n";
    }
}

void Evaluator::printReport(const Metrics& metrics, ostream& out) const {
    out << fixed << setprecision(4);
    out << "Accuracy: " << metrics.accuracy
        << "  (" << metrics.correct << "/" << metrics.total << ")\n\n";

    const int labelW = 8;
    const int numW = 12;

    out << setw(labelW) << "Class"
        << setw(numW) << "Precision"
        << setw(numW) << "Recall"
        << setw(numW) << "F1" << "\n";

    for (const auto& label : kLabels) {
        out << setw(labelW) << label
            << setw(numW) << metrics.precision.at(label)
            << setw(numW) << metrics.recall.at(label)
            << setw(numW) << metrics.f1.at(label) << "\n";
    }

    out << setw(labelW) << "Macro"
        << setw(numW) << metrics.macroPrecision
        << setw(numW) << metrics.macroRecall
        << setw(numW) << metrics.macroF1 << "\n\n";

    printConfusionMatrix(metrics, out);
}
