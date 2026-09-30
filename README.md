# MiniSpamFilter

Multiclass SMS classifier (**Ham / Spam / Scam**) using **Naive Bayes** in C++.

Built as an OOP course project (inheritance for tokenisers, train → evaluate → predict pipeline).

Full design, metrics, and analysis are in the project report (LaTeX PDF).

---

## Requirements

- C++11 or later
- **Windows:** `g++` (e.g. MinGW) — used by `run.bat`
- **Linux / macOS:** `g++` and/or CMake 3.16+
- Dataset files under `data/` (`train.csv`, `test.csv`)

---

## Windows — easiest way

From the project root, double-click **`run.bat`** or in Command Prompt / PowerShell:

```bat
run.bat
```

That will:

1. Create a `build` folder if needed
2. Compile with `g++` into `build\MiniSpamFilter.exe`
3. Run: `build\MiniSpamFilter.exe data\train.csv data\test.csv`

Optional flags after the batch file (passed through to the program):

```bat
run.bat --evaluate-only
```

---

## Linux / macOS

### Option A — g++

```bash
mkdir -p build
g++ -std=c++11 -I include -o build/MiniSpamFilter \
  src/Document.cpp src/Vocabulary.cpp \
  src/SimpleTokeniser.cpp src/StopWordTokeniser.cpp \
  src/NaiveBayesClassifier.cpp src/Evaluator.cpp src/main.cpp

./build/MiniSpamFilter data/train.csv data/test.csv
```

### Option B — CMake

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./MiniSpamFilter ../data/train.csv ../data/test.csv
```

---

## Usage (all platforms)

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
# Windows (after build)
build\MiniSpamFilter.exe
build\MiniSpamFilter.exe data\train.csv data\test.csv
build\MiniSpamFilter.exe data\train.csv data\test.csv --evaluate-only

# Linux / macOS
./build/MiniSpamFilter
./build/MiniSpamFilter data/train.csv data/test.csv
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
run.bat      one-click build + run on Windows
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
