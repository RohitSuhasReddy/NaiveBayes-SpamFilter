# MiniSpamFilter

Multiclass SMS classifier (**Ham / Spam / Scam**) using **Naive Bayes** in C++.

Built as an OOP course project (inheritance for tokenisers, train → evaluate → predict pipeline).

---

## Requirements

- C++11 or later
- **Windows:** `g++` (e.g. MinGW) — used by `run.bat`
- **Linux / macOS:** CMake 3.16+
- Dataset files under `data/` (`train.csv`, `test.csv`)

---

## Windows

From the project root:

```bat
run.bat
```

Optional:

```bat
run.bat --evaluate-only
```

---

## Linux / macOS

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./MiniSpamFilter ../data/train.csv ../data/test.csv
```

Optional (metrics only):

```bash
./MiniSpamFilter ../data/train.csv ../data/test.csv --evaluate-only
```

---

## Project layout

```text
include/          Headers (Document, tokenisers, NaiveBayes, Evaluator)
src/              Implementations and main.cpp
data/             Source dataset, train/test splits, split_dataset.cpp
media/            Figures (class diagram, metrics plots)
build/            Build output (generated)
run.bat           Windows build and run script
CMakeLists.txt    CMake build configuration
README.md         This file
```

---

## Dataset

This project uses **Dataset_10191.csv** from:

**Munoz, M. & Islam, M. (2025).** *A Balanced Dataset for Spam and Smishing Detection using Large Language Models (LLMs).* Mendeley Data, V1.  
DOI: [10.17632/vmg875v4xs.1](https://doi.org/10.17632/vmg875v4xs.1)

| Property | Detail |
|----------|--------|
| Size | 10,191 SMS messages |
| Classes | ham, spam, smishing (3,397 each) |
| Columns | `LABEL`, `TEXT`, `URL`, `EMAIL`, `PHONE` |

In this codebase, labels are normalised to **Ham**, **Spam**, and **Scam** (smishing mapped to Scam). A stratified 80/20 split produces `data/train.csv` and `data/test.csv`.

### Regenerate the train/test split

From the `data/` directory (with `Dataset_10191.csv` present):

```bash
g++ -std=c++11 -o split_dataset split_dataset.cpp
./split_dataset
```

On Windows:

```bat
g++ -std=c++11 -o split_dataset.exe split_dataset.cpp
split_dataset.exe
```

---

## Documentation

| Path | Description |
|------|-------------|
| `media/ClassDiagram.png` | UML class diagram |
| `media/class_dist.png` | Class distribution figure |
| `media/confusion_matrix.png` | Confusion matrix figure |
| `media/metrics_bars.png` | Per-class metrics figure |
| Project report (PDF) | Full design, evaluation, and analysis (submitted separately) |

---

## License

See [LICENSE](LICENSE).
