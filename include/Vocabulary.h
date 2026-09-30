#pragma once

#include <string>
#include <set>
#include <cstddef>

using namespace std;

class Vocabulary {
public:
    void add(const string& word);
    bool contains(const string& word) const;
    size_t size() const;

private:
    set<string> words_;
};
