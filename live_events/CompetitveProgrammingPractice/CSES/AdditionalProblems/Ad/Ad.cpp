#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

int n;
ll ans = 0;
set<simps> rng;
multiset<int> lens;
map<int, vector<int>> idx;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        idx[-cur].push_back(i);
    }

    for (auto& u : idx) {
        for (int i : u.second) {
            simps cur = {i, i};

            auto it = rng.lower_bound(cur);
            if (it != rng.begin()) {
                it--;
                if (it->second == i - 1) {
                    cur.first = it->first;
                    lens.erase(lens.find(it->first - it->second - 1));
                    rng.erase(it);
                }
            }

            it = rng.upper_bound(cur);
            if (it != rng.end()) {
                if (it->first == i + 1) {
                    cur.second = it->second;
                    lens.erase(lens.find(it->first - it->second - 1));
                    rng.erase(it);
                }
            }

            rng.insert(cur);
            lens.insert(cur.first - cur.second - 1);
        }

        ans = max((ll) u.first * *lens.begin(), ans);
    }

    cout << ans << "\n";

	return 0;
}
