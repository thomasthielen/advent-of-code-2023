#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

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
    cout << "T=" << time << " R=" << record << "\n";

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
}