#include <iostream>
#include <vector>
#include <string>

#include "Document.h"
#include "SimpleTokeniser.h"
#include "StopWordTokeniser.h"
#include "NaiveBayesClassifier.h"
#include "Evaluator.h"
#include "ModelIO.h"

// TODO (P4): Wire everything together
// 1. Load train.csv / test.csv
// 2. Tokenize → fill Document::wordCount
// 3. Train NaiveBayesClassifier
// 4. Evaluate on test set
// 5. Optional: interactive CLI for new messages

int main() {
    std::cout << "MiniSpamFilter – Naive Bayes Multiclass SMS Filter\n";
    std::cout << "Classes: Ham / Spam / Scam\n\n";

    // Placeholder – replace with real pipeline
    std::cout << "[P4] Load data, train, evaluate, and start CLI here.\n";

    return 0;
}
