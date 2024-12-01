#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

list<tuple<string,int>> hands;
vector<char> cards {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

void read_hand (const string line) {
    string hand;
    int bid;
    string input = "";
    bool reading_bid = false;
    for (const char& c : line) {
        if (isspace(c)) {
            hand = input;
            reading_bid = true;
            input = "";
        } else {
            input += c;
        }
    }
    bid = stoi(input);
    hands.push_back({hand,bid});
}

// highest value (five of a kind) = 6
// lowest value (high card) = 0
int check_strength(const string& hand) {
    tuple<bool,int> fh = {false,0}; // three of a kind, two pair
    for (const char& card : cards) {
        int occ = 0;
        for (const char& c : hand) {
            if (card == c) {
                occ++;
            }
        }
        if (occ > 5) {
            cout << "Error while checking hand, illegal value of " << occ << "\n";
            return -1; 
        }
        switch (occ) {
            case 5:
            case 4:
              return occ + 1;
              break;
            case 3:
              get<0>(fh) = true; 
              break; 
            case 2:
              get<1>(fh)++;
              break;
        }
    }
    if (get<0>(fh)) {
        if (get<1>(fh) == 1) {
            return 4;   
        }
        return 3;
    }
    return get<1>(fh);

}

int card_value(const char& card) {
    int value = 14;
    for (const char& c : cards) {
        if (card == c) {
            return value;
        }
        --value;
    }
    return -1;
}

bool compare_hands(const tuple<string,int>& t1, const tuple<string,int>& t2) {
    string h1 = get<0>(t1);
    string h2 = get<0>(t2);
    int s1 = check_strength(h1);
    int s2 = check_strength(h2);
    if (s1 == s2) {
        for (int i = 0; i < h1.size(); ++i) {
            if (h1[i] == h2[i]) {
                continue;
            }
            return card_value(h1[i]) < card_value(h2[i]);
        }
    }
    return s1 < s2;
}

int main() {
    fstream file ("test.txt");
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            read_hand(line);
        }
        file.close();
    }
    hands.sort(compare_hands);
    int winnings = 0;
    // cout << "Sorted (weakest to strongest):\n";
    int rank = 1;
    for (const tuple<string,int>& t : hands) {
        // cout << rank << " " << get<0>(t) << "\n";
        winnings += rank * get<1>(t);
        ++rank;
    }
    cout << "total winnings = " << winnings << "\n";
}