# MiniSpamFilter (NaiveBayes-SpamFilter)

Multiclass SMS text classification using **Naive Bayes** in C++ (OOP course project).

**Classes:** Ham / Spam / Scam (Smishing)

**Dataset:** Balanced SMS dataset (A2) — 3,397 messages per class  
Source: [Mendeley Data – DOI 10.17632/vmg875v4xs.1](https://data.mendeley.com/datasets/vmg875v4xs)

---

## Project Structure

```
NaiveBayes-SpamFilter/
├── README.md
├── CMakeLists.txt
├── data/
│   ├── README.md                 # how to get the dataset
│   ├── train.csv                 # (you add after split)
│   └── test.csv                  # (you add after split)
├── include/
│   ├── Document.h
│   ├── Vocabulary.h
│   ├── ITokeniser.h
│   ├── SimpleTokeniser.h
│   ├── StopWordTokeniser.h
│   ├── NGramTokeniser.h
│   ├── RegexTokeniser.h
│   ├── NaiveBayesClassifier.h
│   ├── IClassifier.h
│   ├── Evaluator.h
│   └── ModelIO.h
├── src/
│   ├── Document.cpp
│   ├── Vocabulary.cpp
│   ├── SimpleTokeniser.cpp
│   ├── StopWordTokeniser.cpp
│   ├── NGramTokeniser.cpp
│   ├── RegexTokeniser.cpp
│   ├── NaiveBayesClassifier.cpp
│   ├── Evaluator.cpp
│   ├── ModelIO.cpp
│   └── main.cpp
├── models/                       # saved trained models go here
│   └── .gitkeep
└── docs/
    └── team_roles.md
```

---

## Team Roles

| Person | Role | Owns |
|--------|------|------|
| **P1** | Core ML | `NaiveBayesClassifier`, `IClassifier`, `ModelIO` |
| **P2** | Preprocessing | `ITokeniser` hierarchy, `Document`, `Vocabulary` |
| **P3** | Data & Evaluation | `data/`, `Evaluator` |
| **P4** | Interface & Integration | `main.cpp`, `CMakeLists.txt`, README, glue |

See `docs/team_roles.md` for details.

---

## Build (once code is ready)

```bash
mkdir build && cd build
cmake ..
make
./MiniSpamFilter
```

Or with a simple Makefile if preferred.

---

## Dataset Setup (P3)

1. Download `Dataset_10191.csv` from Mendeley: https://data.mendeley.com/datasets/vmg875v4xs
2. Map labels: `Smishing` → `Scam`
3. Create stratified 80/20 split → `data/train.csv` and `data/test.csv`
