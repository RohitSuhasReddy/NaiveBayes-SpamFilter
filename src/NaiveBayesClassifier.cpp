#include "NaiveBayesClassifier.h"
#include <cmath>
#include <limits>

using namespace std;

void NaiveBayesClassifier::train(const vector<Document>& documents) {
    classDocCounts_.clear();
    classTotalWords_.clear();
    wordCounts_.clear();
    totalDocs_ = 0;

    for (const auto& doc : documents) {
        const string& label = doc.label;
        classDocCounts_[label]++;
        totalDocs_++;

        for (auto it = doc.wordCount.begin(); it != doc.wordCount.end(); ++it) {
            wordCounts_[label][it->first] += it->second;
            classTotalWords_[label] += it->second;
            vocab_.add(it->first);
        }
    }

    trained_ = true;
}

double NaiveBayesClassifier::logPrior(const string& classLabel) const {
    return log(static_cast<double>(classDocCounts_.at(classLabel)) / totalDocs_);
}

double NaiveBayesClassifier::logLikelihood(const string& word,
                                           const string& classLabel) const {
    int count = 0;
    auto classIt = wordCounts_.find(classLabel);
    if (classIt != wordCounts_.end()) {
        auto wordIt = classIt->second.find(word);
        if (wordIt != classIt->second.end()) {
            count = wordIt->second;
        }
    }

    int totalWords = classTotalWords_.at(classLabel);
    int V = static_cast<int>(vocab_.size());

    return log(static_cast<double>(count + 1) / (totalWords + V));
}

map<string, double> NaiveBayesClassifier::predictScores(const Document& doc) const {
    map<string, double> scores;

    if (!trained_ || totalDocs_ == 0) {
        return scores;
    }

    for (auto classIt = classDocCounts_.begin(); classIt != classDocCounts_.end(); ++classIt) {
        const string& label = classIt->first;
        double score = logPrior(label);

        for (auto wordIt = doc.wordCount.begin(); wordIt != doc.wordCount.end(); ++wordIt) {
            score += wordIt->second * logLikelihood(wordIt->first, label);
        }

        scores[label] = score;
    }

    return scores;
}

string NaiveBayesClassifier::predict(const Document& doc) const {
    auto scores = predictScores(doc);

    if (scores.empty()) {
        return "Ham";
    }

    string bestLabel;
    double bestScore = -numeric_limits<double>::infinity();

    for (auto it = scores.begin(); it != scores.end(); ++it) {
        if (it->second > bestScore) {
            bestScore = it->second;
            bestLabel = it->first;
        }
    }

    return bestLabel;
}