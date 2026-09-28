# Dataset (Option A2 – Balanced)

**Source:** A Balanced Dataset for Spam and Smishing Detection using LLMs  
**DOI:** 10.17632/vmg875v4xs.1  
**Link:** https://data.mendeley.com/datasets/vmg875v4xs

- 10,191 messages
- Exactly 3,397 Ham / 3,397 Spam / 3,397 Smishing

## Steps for P3

1. Download `Dataset_10191.csv` from Mendeley.
2. Map original label `Smishing` → `Scam` (or keep `Smishing` if preferred).
3. Perform a **stratified 80/20** train/test split (preserve class balance).
4. Save as:
   - `train.csv`
   - `test.csv`

Expected columns (minimum):
```
LABEL,TEXT
```
Optional extra columns from the original: URL, EMAIL, PHONE (can be ignored by the tokenizer).

Place the final `train.csv` and `test.csv` in this folder.
