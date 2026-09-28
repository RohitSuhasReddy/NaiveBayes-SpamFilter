#include "ModelIO.h"
#include <fstream>

// TODO (P1): Serialize / deserialize the model

bool ModelIO::save(const NaiveBayesClassifier& model, const std::string& filepath) {
    (void)model;
    (void)filepath;
    // Write vocabulary, class counts, word counts, etc.
    return false;
}

bool ModelIO::load(NaiveBayesClassifier& model, const std::string& filepath) {
    (void)model;
    (void)filepath;
    return false;
}
