# Team Roles – MiniSpamFilter

## P1 – Core ML
**Owns:**
- `include/NaiveBayesClassifier.h` + `src/NaiveBayesClassifier.cpp`
- `include/IClassifier.h` (optional polymorphism)
- `include/ModelIO.h` + `src/ModelIO.cpp`

**Tasks:**
- Implement train() and predict() with Laplace smoothing
- Multiclass (Ham / Spam / Scam)
- Optional second simple classifier for comparison
- Save / load trained model

---

## P2 – Preprocessing (OOP focus)
**Owns:**
- `include/ITokeniser.h`
- `include/SimpleTokeniser.h` + `.cpp`
- `include/StopWordTokeniser.h` + `.cpp`
- `include/NGramTokeniser.h` + `.cpp` (optional)
- `include/RegexTokeniser.h` + `.cpp` (optional – strip URLs/numbers)
- `include/Document.h` + `.cpp`
- `include/Vocabulary.h` + `.cpp`

**Tasks:**
- Inheritance hierarchy for tokenizers
- Document holds text, label, wordCount map
- Vocabulary holds the set of known words

---

## P3 – Data & Evaluation
**Owns:**
- Everything under `data/`
- `include/Evaluator.h` + `src/Evaluator.cpp`

**Tasks:**
- Download & clean the balanced A2 dataset
- Stratified 80/20 train/test split
- Accuracy, precision, recall, F1 (per class + overall)
- Confusion matrix
- Optional: simple k-fold

---

## P4 – Interface & Integration
**Owns:**
- `src/main.cpp`
- `CMakeLists.txt`
- `README.md`
- Final glue & demo

**Tasks:**
- CLI: train → evaluate → predict new messages
- Load model and classify user-typed SMS
- Make sure the project builds and runs end-to-end
- Documentation
