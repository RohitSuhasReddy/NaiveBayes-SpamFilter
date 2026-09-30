#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Evaluator {
public:
    static const vector<string> kLabels;

    struct Metrics {
        int total = 0;
        int correct = 0;
        double accuracy = 0.0;

        map<string, double> precision;
        map<string, double> recall;
        map<string, double> f1;

        double macroPrecision = 0.0;
        double macroRecall = 0.0;
        double macroF1 = 0.0;

        // confusion[trueLabel][predictedLabel] = count
        map<string, map<string, int>> confusion;
    };

    Metrics evaluate(const vector<string>& yTrue,
                     const vector<string>& yPred) const;

    void printReport(const Metrics& metrics, ostream& out = cout) const;
    void printConfusionMatrix(const Metrics& metrics, ostream& out = cout) const;

private:
    static double safeDivide(double numerator, double denominator);
};
