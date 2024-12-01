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

vector<vector<char>> field;
int origin; 
int x = -1;
int y = -1;

void print_coords() {
    cout << "x = " << x << ", y = " << y << "\n";
}

int main() {
    fstream file ("test.txt");
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            vector<char> row(line.begin(), line.end());
            field.push_back(row);
        }
        file.close();
    }

    for (int i=0; i < field.size(); ++i){
        for (int j=0; j < field[i].size(); ++j){
            if (field[i][j] == 'S') {
                x = j;
                y = i;
            }
        }
    }
    if (x < 0 || y < 0)
        return -1;

    // check around S for the loop, clockwise and starting with north
    if (field[y-1][x] == '7' || field[y-1][x] == '|' || field[y-1][x] == 'F'){
        y--;
        origin = 6;
    } else if (field[y][x+1] == 'J' || field[y][x+1] == '-' || field[y][x+1] == '7'){
        x++;
        origin = 9;
    } else if (field[y+1][x] == 'J' || field[y+1][x] == '|' || field[y+1][x] == 'L'){
        y++;
        origin = 12;
    } else if (field[y][x-1] == 'L' || field[y][x-1] == '-' || field[y][x-1] == 'F'){
        x--;
        origin = 3;
    } 

    int steps = 0;
    for (;;){
        // print_coords();
        steps++;
        if (field[y][x] == 'S')
            break;
        
        switch (field[y][x]) {
            case '|':
                if (origin == 12)
                    y++;
                else if (origin == 6)
                    y--;
                break;
            case '-':
                if (origin == 9)
                    x++;
                else if (origin == 3)
                    x--;
                break;
            case 'L':
                if (origin == 12) {
                    x++;
                    origin = 9;
                }
                else if (origin == 3) {
                    y--;
                    origin = 6;
                }
                break;
            case 'J':
                if (origin == 12) {
                    x--;
                    origin = 3;
                }
                else if (origin == 9) {
                    y--;
                    origin = 6;
                }
                break;
            case '7':
                if (origin == 9) {
                    y++;
                    origin = 12;
                }
                else if (origin == 6) {
                    x--;
                    origin = 3;
                }
                break;
            case 'F':
                if (origin == 3) {
                    y++;
                    origin = 12;
                }
                else if (origin == 6) {
                    x++;
                    origin = 9;
                }
                break;
        }
    }

    cout << "steps to the point farthest from the starting position\n= " << steps/2 << endl;
}