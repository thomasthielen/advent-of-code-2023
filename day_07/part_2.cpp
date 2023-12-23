#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

list<tuple<string,int>> hands;
vector<char> cards {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

void read_hand (const string& line) {
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

int joker_occ (const string& hand) {
    int occ = 0;
    for (const char& c : hand) {
        if (c == 'J') {
            occ++;
        }
    }
    return occ;
}

// 6 = highest value (five of a kind)
// 0 = lowest value (high card)
int check_strength(const string& hand) {
    tuple<bool,int> fh = {false,0}; // notes three of a kind & counts two pairs
    int J = joker_occ(hand); // counts jokers
    for (const char& card : cards) {
        int occ = 0;
        for (const char& c : hand) {
            if (card == c) {
                occ++;
            }
        }
        if (occ > 5) {
            return -1; 
        }
        switch (occ) {
            // 5 oak, no joker affection
            case 5:
              return 6;
            // 4 oak
            case 4:
              // joker => 5 oak (in any case)
              if (J > 0) {
                return 6;
              }
              return 5;
              break;
            // note occurence of 3 oak
            case 3:
              get<0>(fh) = true; 
              break; 
            // count occurence of 1 more pair
            case 2:
              get<1>(fh)++;
              break;
        }
    }
    if (get<0>(fh)) {
        if (get<1>(fh) == 1) {
            // full house, joker => 5 oak (because both JJJKK and JJKKK => KKKKK)
            if (J > 0) {
                return 6;
            }
            return 4;   
        }
        // 3 oak, joker => 4 oak (e.g. KKKJ3 => KKKK3 and JJJK4 => KKKK4))
        if (J > 0) {
            return 5;
        }
        return 3;
    }
    switch (get<1>(fh)) {
        // 2 pair
        case 2:
          // joker part of pairs => 4 oak (e.g. KKJJ3 => KKKK3)
          if (J == 2) {
            return 5;
          }
          // joker not part of pairs => full house (e.g. e.g. QQKKJ => QQKKK)
          if (J == 1) {
            return 4;
          }
          return 2;
        // 1 pair
        case 1:
          // joker => 3 oak as 3 oak > 2 pair, e.g. QQ4J3 => QQ4Q3 and JJ4K7 => KK4K7
          if (J > 0) {
            return 3;
          }
          return 1;
        // high card
        case 0:
          // joker => 1 pair (e.g. J1234 => 41234)
          if (J == 1) {
            return 1;
          }
          return 0;
    }
    // error strength
    return -1;
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

// TODO: Optimization: check_strength should only be called once and its value stores somewhere
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
    fstream file ("input.txt");
    string line;
    if (file.is_open()) {
        while (getline(file,line)) {
            read_hand(line);
        }
        file.close();
    }
    hands.sort(compare_hands);
    int winnings = 0;
    // cout << "Sorted (weakest to strongest): \n";
    int rank = 1;
    for (const tuple<string,int>& t : hands) {
        // cout << rank << " " << get<0>(t) << "\n";
        winnings += rank * get<1>(t);
        ++rank;
    }
    cout << "total winnings = " << winnings << "\n";
}