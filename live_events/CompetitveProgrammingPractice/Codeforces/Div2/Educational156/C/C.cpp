#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

int t;

void subcase() {
    ll tar;
    string s;
    set<int> rem, bad;
    cin >> s >> tar;

    for (int i = 0; i < s.size(); i++) {
        rem.insert(i);
        if (i < s.size() + 1 and s[i] > s[i + 1]) bad.insert(i);
    }

    while (tar > rem.size()) {
        tar -= rem.size();

        int cur;
        if (bad.size()) {
            cur = *bad.begin();
            bad.erase(cur);
        }
        else {
            auto it = rem.end();
            it--;
            cur = *it;
        }
        rem.erase(cur);

        auto it = rem.lower_bound(cur);
        if (it == rem.begin() or it == rem.end()) continue;
        cur = *it;
        it--;
        if (s[*it] > s[cur]) bad.insert(*it);
    }

    for (int i : rem) {
        tar--;
        if (tar == 0) {
            cout << s[i];
            return;
        }
    }
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
    cout << "\n";
	return 0;
}
