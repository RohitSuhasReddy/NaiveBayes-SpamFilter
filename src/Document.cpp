#include "Document.h"

Document::Document(const std::string& t, const std::string& l)
    : text(t), label(l) {}

void Document::setText(const std::string& t) {
    text = t;
}

void Document::setLabel(const std::string& l) {
    label = l;
}

// TODO (P2): wordCount is filled by the tokenizer + training pipeline
