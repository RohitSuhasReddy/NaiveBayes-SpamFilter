# MiniSpamFilter

Multiclass SMS classifier (**Ham / Spam / Scam**) using **Naive Bayes** in C++.

Built as an OOP course project (inheritance for tokenisers, train → evaluate → predict pipeline).

Full design, metrics, and analysis are in the project report (LaTeX PDF).

---

## Requirements

- C++11 or later
- `g++` **or** CMake 3.16+
- Dataset files under `data/` (`train.csv`, `test.csv`)

---

## Quick start (Windows)

From the project root:

```bat
run.bat
```

This builds `build\MiniSpamFilter.exe` and runs:

```text
build\MiniSpamFilter.exe data\train.csv data\test.csv
```

---

## Build & run (manual)

### Option A — g++

```bash
mkdir -p build
g++ -std=c++11 -I include -o build/MiniSpamFilter \
  src/Document.cpp src/Vocabulary.cpp \
  src/SimpleTokeniser.cpp src/StopWordTokeniser.cpp \
  src/NaiveBayesClassifier.cpp src/Evaluator.cpp src/main.cpp

./build/MiniSpamFilter data/train.csv data/test.csv
```

On Windows, use `build\MiniSpamFilter.exe` instead of `./build/MiniSpamFilter`.

### Option B — CMake

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./MiniSpamFilter ../data/train.csv ../data/test.csv
```

---

## Usage

```text
MiniSpamFilter [train.csv] [test.csv] [--evaluate-only]
```

| Argument | Default | Meaning |
|----------|---------|---------|
| `train.csv` | `data/train.csv` | Training data |
| `test.csv` | `data/test.csv` | Held-out test data |
| `--evaluate-only` | off | Print metrics only (skip interactive SMS prompt) |
| `-h` / `--help` | | Show help |

**Examples**

```bash
# Default paths + interactive predict loop
./build/MiniSpamFilter

# Explicit paths
./build/MiniSpamFilter data/train.csv data/test.csv

# Metrics only
./build/MiniSpamFilter data/train.csv data/test.csv --evaluate-only
```

After evaluation, type an SMS and press Enter to classify it. Empty line or `quit` exits.

---

## Project layout

```text
include/     headers (Document, tokenisers, NaiveBayes, Evaluator)
src/         implementations + main.cpp
data/        Dataset_10191.csv, train.csv, test.csv, split_dataset.py
build/       build output (generated)
```

---

## Dataset

- Source: balanced SMS Ham / Spam / Smishing set (A2)
- Labels used in code: **Ham**, **Spam**, **Scam** (Smishing → Scam)
- Split: stratified 80/20 → `data/train.csv`, `data/test.csv`

To regenerate the split:

```bash
cd data
python3 split_dataset.py
```

---

## Documentation

| File | Description |
|------|-------------|
| `class_diagram.png` | Class diagram (UML) |
| Project report (PDF) | Full documentation, metrics, analysis |

---

## License

See [LICENSE](LICENSE).
