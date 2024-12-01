#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <map>

using namespace std;
typedef long long ll;

vector<vector<int>> histories;

vector<int> read_values(const string& line) {
    vector<int> v;
    string val = "";
    for (const char& c : line){
        if (isdigit(c) || c == '-') {
            val += c;
            continue;
        }
        if (val.size() > 0) {
            v.push_back(stoi(val));
        }
        val = "";
    }
    if (val.size() > 0) {
        v.push_back(stoi(val));
    }
    return v;
}

vector<int> produce_diff_seq(vector<int> v) {
    vector<int> seq;
    for (int i = 0; i < v.size() - 1; ++i) {
        seq.push_back(v[i+1] - v[i]);
    }
    return seq;
}

bool check_diff_seq(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] != 0)
            return true;
    }
    return false;
}

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    fstream file ("test.txt");
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vector<int> h = read_values(line);
            histories.push_back(h);
        }
        file.close();
    }
    ll sum = 0;
    for (vector<int> h : histories) {
        vector<int> first_values;
        first_values.push_back(h[0]);
        vector<int> seq = h;
        while (check_diff_seq(seq)){
            seq = produce_diff_seq(seq);
            if (seq.size() < 1) 
                break;
            first_values.push_back(seq[0]);
        }
        int prediction = 0;
        for (int r = first_values.size()-1; r >= 0; --r){
            prediction = first_values[r] - prediction;
        }
        sum += prediction;
    }
    cout << "sum = " << sum << "\n";

    // Execution time (sec) = 0.008
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Execution time (sec) = " <<  (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<endl;
}