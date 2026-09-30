#include "Document.h"
#include "StopWordTokeniser.h"
#include "NaiveBayesClassifier.h"
#include "Evaluator.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

static const char* RESET = "\033[0m";
static const char* BOLD = "\033[1m";
static const char* DIM = "\033[2m";
static const char* GREEN = "\033[32m";
static const char* YELLOW = "\033[33m";
static const char* RED = "\033[31m";
static const char* MAGENTA = "\033[35m";
static const char* WHITE = "\033[97m";

static void enableColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) {
        return;
    }
    mode |= 0x0004;  // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleMode(hOut, mode);
#endif
}

static const char* labelColor(const string& label) {
    if (label == "Ham") {
        return GREEN;
    }
    if (label == "Spam") {
        return YELLOW;
    }
    if (label == "Scam") {
        return RED;
    }
    return WHITE;
}

static void printUsage() {
    cout << "MiniSpamFilter - Naive Bayes Ham / Spam / Scam classifier\n\n"
         << "Usage:\n"
         << "  MiniSpamFilter [train.csv] [test.csv] [--evaluate-only]\n\n"
         << "  train.csv = data/train.csv\n"
         << "  test.csv  = data/test.csv\n\n"
         << "  --evaluate-only   skip the SMS prompt\n";
}

static string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && isspace(static_cast<unsigned char>(s[start]))) {
        start++;
    }
    size_t end = s.size();
    while (end > start && isspace(static_cast<unsigned char>(s[end - 1]))) {
        end--;
    }
    return s.substr(start, end - start);
}

static vector<string> parseCsvLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (inQuotes) {
            if (c == '"') {
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    field.push_back('"');
                    ++i;
                } else {
                    inQuotes = false;
                }
            } else {
                field.push_back(c);
            }
        } else if (c == '"') {
            inQuotes = true;
        } else if (c == ',') {
            fields.push_back(field);
            field.clear();
        } else {
            field.push_back(c);
        }
    }
    fields.push_back(field);
    return fields;
}

static vector<Document> loadCsv(const string& path, const ITokeniser& tokeniser) {
    ifstream in(path);
    if (!in) {
        throw runtime_error("Could not open CSV: " + path);
    }

    string headerLine;
    if (!getline(in, headerLine)) {
        throw runtime_error("Empty CSV: " + path);
    }
    if (!headerLine.empty() && static_cast<unsigned char>(headerLine[0]) == 0xEF) {
        if (headerLine.size() >= 3) {
            headerLine = headerLine.substr(3);
        }
    }

    auto header = parseCsvLine(headerLine);
    int labelCol = -1;
    int textCol = -1;
    for (int i = 0; i < static_cast<int>(header.size()); ++i) {
        string name = trim(header[i]);
        if (name == "LABEL") {
            labelCol = i;
        } else if (name == "TEXT") {
            textCol = i;
        }
    }
    if (labelCol < 0 || textCol < 0) {
        throw runtime_error("CSV must have LABEL and TEXT columns: " + path);
    }

    vector<Document> docs;
    string line;
    while (getline(in, line)) {
        if (trim(line).empty()) {
            continue;
        }
        auto fields = parseCsvLine(line);
        if (labelCol >= static_cast<int>(fields.size()) ||
            textCol >= static_cast<int>(fields.size())) {
            continue;
        }

        Document doc;
        doc.label = trim(fields[labelCol]);
        doc.text = fields[textCol];
        if (doc.label != "Ham" && doc.label != "Spam" && doc.label != "Scam") {
            continue;
        }
        doc.buildWordCount(tokeniser);
        docs.push_back(doc);
    }

    if (docs.empty()) {
        throw runtime_error("No labelled rows in: " + path);
    }
    return docs;
}

static void printColoredReport(const Evaluator::Metrics& metrics) {
    cout << fixed << setprecision(4);
    cout << "\n" << BOLD << "Test evaluation" << RESET << "\n";
    cout << string(52, '-') << "\n";
    cout << "Accuracy  " << GREEN << BOLD << metrics.accuracy << RESET
         << DIM << "  (" << metrics.correct << "/" << metrics.total << ")"
         << RESET << "\n\n";

    const int labelW = 10;
    const int numW = 12;

    cout << BOLD
         << setw(labelW) << "Class"
         << setw(numW) << "Precision"
         << setw(numW) << "Recall"
         << setw(numW) << "F1" << RESET << "\n";

    for (size_t i = 0; i < Evaluator::kLabels.size(); ++i) {
        const string& label = Evaluator::kLabels[i];
        cout << labelColor(label)
             << setw(labelW) << label << RESET
             << setw(numW) << metrics.precision.at(label)
             << setw(numW) << metrics.recall.at(label)
             << setw(numW) << metrics.f1.at(label) << "\n";
    }

    cout << MAGENTA
         << setw(labelW) << "Macro" << RESET
         << setw(numW) << metrics.macroPrecision
         << setw(numW) << metrics.macroRecall
         << setw(numW) << metrics.macroF1 << "\n\n";

    const int cellW = 10;
    cout << DIM << "Confusion matrix  (rows = true, columns = predicted)"
         << RESET << "\n";
    cout << setw(cellW) << " ";
    for (size_t i = 0; i < Evaluator::kLabels.size(); ++i) {
        const string& pred = Evaluator::kLabels[i];
        cout << labelColor(pred) << setw(cellW) << pred << RESET;
    }
    cout << "\n";

    for (size_t r = 0; r < Evaluator::kLabels.size(); ++r) {
        const string& actual = Evaluator::kLabels[r];
        cout << labelColor(actual) << setw(cellW) << actual << RESET;
        for (size_t c = 0; c < Evaluator::kLabels.size(); ++c) {
            const string& pred = Evaluator::kLabels[c];
            int count = 0;
            auto rowIt = metrics.confusion.find(actual);
            if (rowIt != metrics.confusion.end()) {
                auto colIt = rowIt->second.find(pred);
                if (colIt != rowIt->second.end()) {
                    count = colIt->second;
                }
            }
            if (actual == pred) {
                cout << GREEN << setw(cellW) << count << RESET;
            } else {
                cout << setw(cellW) << count;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

static void predictLoop(const NaiveBayesClassifier& clf, const ITokeniser& tokeniser) {
    cout << "\nType an SMS to classify (empty line or 'quit' to exit):\n";
    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) {
            break;
        }
        string text = trim(line);
        if (text.empty() || text == "quit" || text == "exit") {
            break;
        }

        Document doc;
        doc.text = text;
        doc.buildWordCount(tokeniser);

        string pred = clf.predict(doc);
        cout << "Prediction: " << BOLD << labelColor(pred) << pred << RESET << "\n";

        auto scores = clf.predictScores(doc);
        cout << "Log scores:";
        for (auto it = scores.begin(); it != scores.end(); ++it) {
            cout << "  " << labelColor(it->first) << it->first << RESET
                 << "=" << it->second;
        }
        cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    enableColors();

    string trainPath = "data/train.csv";
    string testPath = "data/test.csv";
    bool evaluateOnly = false;
    int positional = 0;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            printUsage();
            return 0;
        }
        if (arg == "--evaluate-only") {
            evaluateOnly = true;
            continue;
        }
        if (arg[0] == '-') {
            cerr << RED << "Unknown option: " << arg << RESET << "\n";
            printUsage();
            return 1;
        }
        if (positional == 0) {
            trainPath = arg;
        } else if (positional == 1) {
            testPath = arg;
        } else {
            cerr << RED << "Too many arguments." << RESET << "\n";
            printUsage();
            return 1;
        }
        positional++;
    }

    try {
        cout << "MiniSpamFilter - Naive Bayes Ham / Spam / Scam\n\n";
        StopWordTokeniser tokeniser;

        cout << YELLOW << "Loading data..." << RESET << "\n";
        cout << "Loading train: " << trainPath << "\n";
        auto trainDocs = loadCsv(trainPath, tokeniser);
        cout << "  " << trainDocs.size() << " documents\n";
        cout << "Loading test:  " << testPath << "\n";
        auto testDocs = loadCsv(testPath, tokeniser);
        cout << "  " << testDocs.size() << " documents\n";

        NaiveBayesClassifier clf;
        cout << "\n" << YELLOW << "Training Naive Bayes..." << RESET << "\n";
        clf.train(trainDocs);
        cout << GREEN << "Done." << RESET << "\n";

        vector<string> yTrue;
        vector<string> yPred;
        yTrue.reserve(testDocs.size());
        yPred.reserve(testDocs.size());
        for (const auto& doc : testDocs) {
            yTrue.push_back(doc.label);
            yPred.push_back(clf.predict(doc));
        }

        Evaluator evaluator;
        Evaluator::Metrics metrics = evaluator.evaluate(yTrue, yPred);
        printColoredReport(metrics);

        if (!evaluateOnly) {
            predictLoop(clf, tokeniser);
        }
    } catch (const exception& ex) {
        cerr << RED << BOLD << "Error: " << ex.what() << RESET << "\n";
        return 1;
    }

    return 0;
}
