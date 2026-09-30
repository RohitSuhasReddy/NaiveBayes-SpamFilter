# MiniSpamFilter

Multiclass SMS classifier (**Ham / Spam / Scam**) using **Naive Bayes** in C++.

Built as an OOP course project (inheritance for tokenisers, train → evaluate → predict pipeline).

Full design, metrics, and analysis are in the project report (LaTeX PDF).

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
