#include <bits/stdc++.h>
using namespace std;

// Stratified 80/20 split of Dataset_10191.csv into train.csv and test.csv.
// Maps labels: ham -> Ham, spam -> Spam, smishing -> Scam.
// Fixed seed (42) for a reproducible shuffle within each class.

struct Row {
    string label;
    string text;
    string url;
    string email;
    string phone;
};

static string trim(const string& s) {
    size_t a = 0;
    while (a < s.size() && isspace(static_cast<unsigned char>(s[a]))) a++;
    size_t b = s.size();
    while (b > a && isspace(static_cast<unsigned char>(s[b - 1]))) b--;
    return s.substr(a, b - a);
}

static string toLower(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
    }
    return s;
}

static vector<string> parseCsvLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (inQuotes) {
            if (c == '"') {
                if (i + 1 < line.size() && line[i + 1] == '"') {
                    field.push_back('"');
                    ++i;
                } else {
                    inQuotes = false;
                }
            } else {
                field.push_back(c);
            }
        } else if (c == '"') {
            inQuotes = true;
        } else if (c == ',') {
            fields.push_back(field);
            field.clear();
        } else {
            field.push_back(c);
        }
    }
    fields.push_back(field);
    return fields;
}

static string csvEscape(const string& s) {
    bool needQuotes = false;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ',' || s[i] == '"' || s[i] == '\n' || s[i] == '\r') {
            needQuotes = true;
            break;
        }
    }
    if (!needQuotes) return s;

    string out = "\"";
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '"') out += "\"\"";
        else out.push_back(s[i]);
    }
    out += "\"";
    return out;
}

static string mapLabel(const string& raw) {
    string l = toLower(trim(raw));
    if (l == "ham") return "Ham";
    if (l == "spam") return "Spam";
    if (l == "smishing") return "Scam";
    return trim(raw);
}

int main() {
    const string srcPath = "Dataset_10191.csv";
    const string trainPath = "train.csv";
    const string testPath = "test.csv";

    ifstream in(srcPath.c_str());
    if (!in) {
        cerr << "Missing " << srcPath << "\n";
        return 1;
    }

    string headerLine;
    if (!getline(in, headerLine)) {
        cerr << "Empty CSV\n";
        return 1;
    }
    if (headerLine.size() >= 3 &&
        static_cast<unsigned char>(headerLine[0]) == 0xEF &&
        static_cast<unsigned char>(headerLine[1]) == 0xBB &&
        static_cast<unsigned char>(headerLine[2]) == 0xBF) {
        headerLine = headerLine.substr(3);
    }

    vector<string> header = parseCsvLine(headerLine);
    int labelCol = -1, textCol = -1, urlCol = -1, emailCol = -1, phoneCol = -1;
    for (int i = 0; i < (int)header.size(); i++) {
        string name = trim(header[i]);
        if (name == "LABEL") labelCol = i;
        else if (name == "TEXT") textCol = i;
        else if (name == "URL") urlCol = i;
        else if (name == "EMAIL") emailCol = i;
        else if (name == "PHONE") phoneCol = i;
    }
    if (labelCol < 0 || textCol < 0) {
        cerr << "CSV must have LABEL and TEXT columns\n";
        return 1;
    }

    map<string, vector<Row> > byLabel;
    string line;
    while (getline(in, line)) {
        if (trim(line).empty()) continue;
        vector<string> fields = parseCsvLine(line);
        if (labelCol >= (int)fields.size() || textCol >= (int)fields.size()) continue;

        Row r;
        r.label = mapLabel(fields[labelCol]);
        r.text = fields[textCol];
        r.url = (urlCol >= 0 && urlCol < (int)fields.size()) ? fields[urlCol] : "";
        r.email = (emailCol >= 0 && emailCol < (int)fields.size()) ? fields[emailCol] : "";
        r.phone = (phoneCol >= 0 && phoneCol < (int)fields.size()) ? fields[phoneCol] : "";

        if (r.label != "Ham" && r.label != "Spam" && r.label != "Scam") continue;
        byLabel[r.label].push_back(r);
    }
    in.close();

    mt19937 rng(42);
    vector<Row> train, test;

    for (map<string, vector<Row> >::iterator it = byLabel.begin();
         it != byLabel.end(); ++it) {
        vector<Row>& rows = it->second;
        shuffle(rows.begin(), rows.end(), rng);

        int n = (int)rows.size();
        int nTest = (int)(n * 0.2 + 0.5);
        int nTrain = n - nTest;

        for (int i = 0; i < nTrain; i++) train.push_back(rows[i]);
        for (int i = nTrain; i < n; i++) test.push_back(rows[i]);

        cout << it->first << ": train=" << nTrain << ", test=" << nTest << "\n";
    }

    shuffle(train.begin(), train.end(), rng);
    shuffle(test.begin(), test.end(), rng);

    auto writeCsv = [&](const string& path, const vector<Row>& data) {
        ofstream out(path.c_str());
        out << "LABEL,TEXT,URL,EMAIL,PHONE\n";
        for (size_t i = 0; i < data.size(); i++) {
            const Row& r = data[i];
            out << csvEscape(r.label) << ","
                << csvEscape(r.text) << ","
                << csvEscape(r.url) << ","
                << csvEscape(r.email) << ","
                << csvEscape(r.phone) << "\n";
        }
        out.close();
        cout << "Wrote " << path << " (" << data.size() << " rows)\n";
    };

    writeCsv(trainPath, train);
    writeCsv(testPath, test);

    return 0;
}
