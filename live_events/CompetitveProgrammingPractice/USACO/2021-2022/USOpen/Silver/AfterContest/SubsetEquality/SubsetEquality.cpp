#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<char, char> simps;

bool IsPossiblePair(const string& s, const string& t, const char a, const char b) {
    string NewS, NewT;
    for (char c : s) {
        if (c == a or c == b) NewS += c;
    }
    for (char c : t) {
        if (c == a or c == b) NewT += c;
    }
    return (NewS == NewT);
}

int main() {
    int Q;
    string s, t;
    vector<int> FreqS(18), FreqT(18);
    set<simps> PossiblePairs;
    cin >> s >> t >> Q;
    for (char c : s) FreqS[c - 'a']++;
    for (char c : t) FreqT[c - 'a']++;
    for (char a = 'a'; a < 'r'; a++) {
        for (char b = a + 1; b <= 'r'; b++) {
            if (IsPossiblePair(s, t, a, b)) {
                PossiblePairs.insert({a, b});
                PossiblePairs.insert({b, a});
            }
        }
    }
    for (int i = 0; i < Q; i++) {
        bool Works = true;
        string Query;
        cin >> Query;
        for (char c : Query) {
            if (FreqS[c - 'a'] != FreqT[c - 'a']) {
                Works = false;
                break;
            }
        }
        if (Works) {
            for (int j = 0; j < Query.size() - 1; j++) {
                char a = Query[j];
                for (int k = j + 1; k < Query.size(); k++) {
                    char b = Query[k];
                    if (PossiblePairs.count({a, b}) == 0) {
                        Works = false;
                        break;
                    }
                }
                if (not Works) break;
            }
        }
        if (Works) cout << "Y";
        else cout << "N";
    }
    cout << "\n";
    return 0;
}
