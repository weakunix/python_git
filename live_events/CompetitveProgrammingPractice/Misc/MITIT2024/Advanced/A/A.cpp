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
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define mkpr make_pair
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

int q;
vector<map<int, ll>> v;

int main() {
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int m, k;
            cin >> m >> k;
            v.pb({{m, k}});
            continue;
        }
        if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--; y--;
            v.pb(v[x]);
            for (auto& u : v[y]) v.back()[u.first] += u.second;
            continue;
        }
        if (t == 3) {
            int x, m, k;
            cin >> x >> m >> k;
            x--;
            v.pb(v[x]);
            if (v.back()[m] >= k) v.back()[m] -= k;
            else v.back()[m] += k;
            if (not v.back()[m]) v.back().erase(m);
            continue;
        }
        int x;
        cin >> x;
        x--;
        cout << v[x].begin()->first << "\n";
    }
	return 0;
}
