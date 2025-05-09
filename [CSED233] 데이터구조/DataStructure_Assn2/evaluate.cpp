#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string removeSpaces(string str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
    str.erase(find_if(str.rbegin(), str.rend(),
                      [](unsigned char ch) { return !isspace(ch); })
                      .base(),
              str.end());
    return str;
}

void readFile(const string &filename, vector<string> &lines) {
    string line;
    int task_num = 0;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        exit(1);
    }

    while (getline(fin, line)) {
        // Trim and then check if it's a new task
        line = removeSpaces(line);
        if (!line.empty() && line.substr(0, 6) == "[Task ") {
            task_num++;
            lines.push_back(line);
        } else if (task_num > 0) {
            // Append this line to the last task, ensuring it's trimmed
            lines[task_num - 1] += "\n" + line;
        }
    }
    fin.close();
}

int main(int argc, char **argv) {
    vector<int> scores;
    int total_score = 0;
    vector<string> submit, answer;

    if (argc == 1) {
        vector<int> sample = {1, 1, 3, 2, 3, 2, 3};
        scores = sample;
    } else {
        for (int i = 1; i < argc; ++i) {
            scores.push_back(atoi(argv[i]));
        }
    }

    readFile("submit.txt", submit);
    readFile("answer.txt", answer);

    for (size_t i = 0; i < min(submit.size(), answer.size()); ++i) {
        if (submit[i] == answer[i]) {
            total_score += scores[i];
        }
    }
    cout << "Your score is " << total_score << endl;
    return 0;
}
