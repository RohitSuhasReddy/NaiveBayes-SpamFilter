#pragma once

#include <string>
#include "NaiveBayesClassifier.h"

/**
 * Save / load a trained NaiveBayesClassifier to/from disk.
 */
class ModelIO {
public:
    static bool save(const NaiveBayesClassifier& model, const std::string& filepath);
    static bool load(NaiveBayesClassifier& model, const std::string& filepath);
};
