#!/usr/bin/env python3
"""Stratified 80/20 split of Dataset_10191.csv into train.csv and test.csv"""

import csv
import random
from collections import defaultdict
from pathlib import Path

random.seed(42)  

data_dir = Path(__file__).resolve().parent
src = data_dir / "Dataset_10191.csv"

if not src.exists():
    raise FileNotFoundError(f"Missing {src}")

rows_by_label = defaultdict(list)

with open(src, newline="", encoding="utf-8", errors="replace") as f:
    reader = csv.DictReader(f)
    fieldnames = reader.fieldnames
    for row in reader:
        label = row["LABEL"].strip().lower()
        if label == "ham":
            row["LABEL"] = "Ham"
        elif label == "spam":
            row["LABEL"] = "Spam"
        elif label == "smishing":
            row["LABEL"] = "Scam"
        rows_by_label[row["LABEL"]].append(row)

train, test = [], []

for label, rows in sorted(rows_by_label.items()):
    random.shuffle(rows)
    n = len(rows)
    n_test = int(round(n * 0.2))
    train.extend(rows[: n - n_test])
    test.extend(rows[n - n_test :])
    print(f"{label}: train={n - n_test}, test={n_test}")

random.shuffle(train)
random.shuffle(test)

for name, data in [("train.csv", train), ("test.csv", test)]:
    path = data_dir / name
    with open(path, "w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(data)
    print(f"Wrote {path} ({len(data)} rows)")