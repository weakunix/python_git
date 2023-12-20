#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const char psbl[4] = {'A', 'C', 'G', 'T'};

string s, ans;
set<char> vis;

int main() {
    cin >> s;
    for (char c : s) {
        vis.insert(c);
        if (vis.size() < 4) continue;
        vis.clear();
        ans += c;
    }

    for (char c : psbl) {
        if (not vis.count(c)) {
            ans += c;
            break;
        }
    }

    cout << ans << "\n";

    return 0;
}
