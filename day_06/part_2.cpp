#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <chrono> 

using namespace std;

list<string> lines;

unsigned long long extract_numbers (const string line) {
    string num = "";
    for (const char& c : line) {
        if (isdigit(c)) {
            num += c;
        } 
    }
    if (num.size() > 0) {
        return stoull(num);
    }
}

int main() {
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    fstream file ("input.txt");
    string line;
    if (file.is_open()) {
        while(getline(file,line)) {
            lines.push_back(line);
        }
        file.close();
    }

    unsigned long long time = extract_numbers(lines.front());
    unsigned long long record = extract_numbers(lines.back());

    // idea: the solution is symmetrical. start from the middle and go in one direction until
    // you do not beat the record anymore. then multiply by 2 and handle odd/even time.
    int sum = 0;
    for (unsigned long long t = time/2, s = time/2 ; t >= 0, s <= time; --t, ++s) {
        if (t * s <= record) {
            break;
        }
        sum++;
    }
    sum *= 2;
    if (time % 2 == 0) {
        sum -= 1;
    }

    cout << sum << "\n";
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Execution time (sec) = " <<  (chrono::duration_cast<chrono::microseconds>(end - begin).count()) /1000000.0  <<endl;
}