#include "SimpleTokeniser.h"
#include <cctype>

using namespace std;

vector<string> SimpleTokeniser::tokenise(const string& text) const {
    vector<string> tokens;
    string current;

    for (unsigned char ch : text) {
        if (isalnum(ch)) {
            current.push_back(static_cast<char>(tolower(ch)));
        } else if (!current.empty()) {
            tokens.push_back(current);
            current.clear();
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}
