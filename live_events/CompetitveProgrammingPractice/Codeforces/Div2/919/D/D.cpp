#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t;

void subcase() {
    int n, q;
    bool done = false;
    ll sz = 0;
    vector<simps> vals;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        ll b, x;
        cin >> b >> x;
        if (done) continue;
        if (b == 1) {
            sz++;
            vals.push_back({sz, x});
        }
        else {
            if ((ll) 1e18 / sz < x + 1) {
                done = true;
                continue;
            }
            sz *= (x + 1);
        }
    }

    for (int i = 0; i < q; i++) {
        ll idx;
        cin >> idx;
        while (true) {
            simps cur = {idx, 1e9};
            auto it = upper_bound(all(vals), cur);
            it--;
            if (idx % it->first == 0) {
                cout << it->second << " ";
                break;
            }
            idx %= it->first;
        }
    }
    cout << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
