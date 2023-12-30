#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
typedef long long ll;

vector<int> read_values(const string& line) {
    vector<int> v;
    string val = "";
    for (const char& c : line){
        if (isdigit(c) || c == '-') {
            val += c;
            continue;
        }
        if (val.size() > 0)
            v.push_back(stoi(val));
        val = "";
    }
    if (val.size() > 0) 
        v.push_back(stoi(val));
    return v;
}

ll recursive_search(vector<int> v) {
    bool anchor = true;
    for (int i = 0; i < v.size(); ++i)
        if (v[i] != 0)
            anchor = false;
    if (anchor)
        return 0;
    vector<int> next;
    for (int i = 0; i < v.size() - 1; ++i) 
        next.push_back(v[i+1] - v[i]);
    return v[v.size()-1] + recursive_search(next);
}

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    vector<vector<int>> histories;
    fstream file ("input.txt");
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vector<int> h = read_values(line);
            histories.push_back(h);
        }
        file.close();
    }
    ll sum = 0;
    for (vector<int> h : histories)
        sum += recursive_search(h);
    cout << "sum = " << sum << endl;
    // Execution time (sec) = 0.0075
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Execution time (sec) = " <<  (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<endl;
}