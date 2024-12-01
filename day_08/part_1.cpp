#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <map>

using namespace std;

string left_right;
map<string, pair<string,string>> nodes;

vector<string> read_node(const string& line) {
    vector<string> v;
    string val = "";
    for (const char& c : line){
        if (isalpha(c)) {
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

bool cmp_nodes(const tuple<string,string,string>& n1, const tuple<string,string,string>& n2) {
    return get<0>(n1) < get<0>(n2);
}

int main() {
    fstream file ("test.txt");
    string line;
    if (file.is_open()) {
        getline(file,line);
        left_right = line;
        getline(file,line);
        while (getline(file,line)) {
            vector<string> v = read_node(line);
            nodes.insert({v[0], pair<string,string>(v[1],v[2])});
        }
        file.close();
    }

    int i = 0;
    pair<string, string> node = nodes["AAA"];
    int steps = 0;
    while (true) {
        ++steps;
        string next;
        if (left_right[i] == 'L') {
            next = get<0>(node);
        } else {
            next = get<1>(node);
        }
        node = nodes[next];
        if (i < left_right.size() - 1) {
            ++i;
        } else {
            i = 0;
        }
        if (next == "ZZZ") {
            break;
        }
    }
    cout << "steps = " << steps << "\n";
}