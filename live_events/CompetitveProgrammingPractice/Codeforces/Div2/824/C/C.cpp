#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

string Subcase() {
    int n;
    string t, ans = "";
    cin >> n >> t;
    vector<char> mapping(26, '.');
    vector<set<char>> possible(26);
    for (int i = 0; i < 26; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (c - 'a' != i) possible[i].insert(c);
        }
    }

    for (char c : t) {
        int cur = c - 'a';
        if (mapping[cur] == '.') {
            mapping[cur] = *possible[cur].begin();
            possible[cur].clear();

            int notpossible = cur;
            for (int i 

            bool done = false;
            while (not done) {
                done = true;
                for (int i = 0; i < 26; i++) {
                    if (possible[i].size() == 1) {
                        done = false;
                        mapping[i] = *possible[i].begin();
                        for (int j = 0; j < 26; j++) possible[j].erase(mapping[i]);
                    }
                }
            }
        }
        ans += mapping[cur];
    }
    
     return ans;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";

	return 0;
}
