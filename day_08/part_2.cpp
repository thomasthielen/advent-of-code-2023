#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <map>
#include <numeric>

using namespace std;

typedef unsigned long long ull;

string left_right;
map<string, pair<string,string>> nodes;
vector<tuple<string,string,string>> flow;
vector<int> cycle_length;

vector<string> read_node(const string& line) {
    vector<string> v;
    string val = "";
    for (const char& c : line){
        if (isalpha(c) || isdigit(c)) {
            val += c;
            continue;
        }
        if (val.size() > 0) {
            v.push_back(val);
        }
        val = "";
    }
    return v;
}

bool check_arrival() {
    for (const int& c : cycle_length) 
        if (c == 0) 
            return false;
    return true;
}

ull gcd(ull a, ull b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 

ull findlcm(vector<int> v) {
    ull result = v[0];
    for (int i = 1; i < v.size(); ++i)
        result = (((result * v[i])) / (gcd(v[i], result)));
    return result;
}

int main() {
    fstream file ("input.txt");
    string line;
    if (file.is_open()) {
        getline(file,line);
        left_right = line;
        getline(file,line);
        while (getline(file,line)) {
            vector<string> v = read_node(line);
            nodes.insert({v[0], pair<string,string>(v[1],v[2])});
            if (v[0][2] == 'A') {
                flow.push_back({v[0],v[1],v[2]});
                cycle_length.push_back(0);
            }
        }
        file.close();
    }

    int i = 0;
    ull steps = 0;
    for (;;) {
        ++steps;
        bool l_r = left_right[i] == 'L';
        for (int j = 0; j < flow.size(); ++j) {
            string next;
            if (l_r)
                next = get<1>(flow[j]);
            else
                next = get<2>(flow[j]);
            flow[j] = {next, nodes[next].first, nodes[next].second};
            if (get<0>(flow[j])[2] == 'Z') 
                cycle_length[j] = steps;
        }

        if (i < left_right.size() - 1)
            ++i;
        else
            i = 0;

        if (check_arrival())
            break;
    }

    steps = findlcm(cycle_length);
    cout << "steps = " << steps << "\n";
}