#pragma once

#include <string>
#include <vector>
#include "Document.h"

/**
 * Optional interface so NaiveBayes can be one implementation among others
 * (polymorphism showcase).
 */
class IClassifier {
public:
    virtual ~IClassifier() = default;

    virtual void train(const std::vector<Document>& documents) = 0;
    virtual std::string predict(const Document& doc) = 0;
};
