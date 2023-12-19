#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <chrono> 

using namespace std;

list<string> lines;
list<unsigned long long> seeds;
list<vector<unsigned long long>> seeds_map;
list<list<vector<unsigned long long>>> maps;

vector<unsigned long long> extract_numbers (const string line) {
    vector<unsigned long long> v;
    string num = "";
    for (const char& c : line) {
        if (isdigit(c)) {
            num += c;
        } else if (num.size() > 0) {
            // THIS TOOK ME WAY TOO LONG:
            // numbers larger than 2 billion lead to std::out_of_range during runtime. Fix: "unsigned long long" instead of "int" and "stoull" instead of "stoi"
            // this really should have been obvious, but I may be a bit noobish at handling big numbers
            v.push_back(stoull(num));
            num = "";
        }
    }
    if (num.size() > 0) {
        v.push_back(stoull(num));
    }
    return v;
}

void read_seeds () {
    vector<unsigned long long> v = extract_numbers(lines.front());
    for (const unsigned long long& seed : v) {
        seeds.push_back(seed);
    }
}

void map_seeds () {
    if (seeds.size() == 0 || seeds.size() % 2 != 0) {
        cout << "Error while mapping seeds\n";
        cout << "seeds.size() = " << seeds.size() << "\n";
        return;
    }
    unsigned n = 0;
    for (list<unsigned long long>::iterator it=seeds.begin(); next(it) != seeds.end(); ++it, ++n) {
        if (n % 2 == 0) {
            vector<unsigned long long> v = {*it, *it + *(next(it))};
            seeds_map.push_back(v);
        }
    }
}

void map_steps () {
    list<vector<unsigned long long>> map;
    for (const string& line : lines) {
        if (line.size() == 0) {
            continue;
        }
        if (line.find("map") != std::string::npos) {
            // save the collected ranges in the respective map
            maps.push_back(map);
            map.clear();
        } else if (isdigit(line[0])) {
            // collect all ranges of this map (all of this is already coded for the REVERSE case)
            vector<unsigned long long> v = extract_numbers(line);
            vector<unsigned long long> translator = {v[0], v[0] + v[2], v[1] - v[0]};
            map.push_back(translator);
        }
    }
    if (map.size() > 0) {
        maps.push_back(map);
    }
}

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    fstream file ("test.txt");
    string line;
    if (file.is_open()) {
        while(getline(file,line)) {
            lines.push_back(line);
        }
        file.close();
    }

    read_seeds();
    map_seeds();

    map_steps();
    maps.reverse();

    for (unsigned long long i = 0; i < 1000; ++i) {
        // the traveller t starts from its destination, given by i
        unsigned long long t = i;
        // for each map t checks where it'll have to go next
        for (const list<vector<unsigned long long>>& map : maps) {
            for (const vector<unsigned long long>& v : map) {
                if (v[0] <= t && t < v[1]) {
                    t += v[2];
                    break;
                }
            }
        }
        // after arriving at a possible source seed, check whether this one really exists
        for (const vector<unsigned long long>& v : seeds_map) {
            if (v[0] <= t && t < v[1]) {
                cout << "Traveller " << i << " arrived at seed " << t << "!\n";
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::cout << "Execution time (sec) = " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0  <<std::endl;
                return 1;
            }
        }
    }
    return 0;
}

