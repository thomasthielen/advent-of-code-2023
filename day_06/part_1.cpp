#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

using namespace std;

list<string> lines;

vector<int> extract_numbers (const string line) {
    vector<int> v;
    string num = "";
    for (const char& c : line) {
        if (isdigit(c)) {
            num += c;
        } else if (num.size() > 0) {
            v.push_back(stoull(num));
            num = "";
        }
    }
    if (num.size() > 0) {
        v.push_back(stoull(num));
    }
    return v;
}

int main() {
    fstream file ("input.txt");
    string line;
    if (file.is_open()) {
        while(getline(file,line)) {
            lines.push_back(line);
        }
        file.close();
    }

    vector<int> time = extract_numbers(lines.front());
    vector<int> record = extract_numbers(lines.back());

    int prod = 1;
    for (int i = 0; i < time.size(); ++i) {
        int sum = 0;
        for (int t = 0, s = time[i]; t <= time[i], s >= 0; ++t, --s) {
            if (t * s > record[i]) {
                sum++;
            }
        }
        prod *= sum; 
    }
    cout << prod;
}