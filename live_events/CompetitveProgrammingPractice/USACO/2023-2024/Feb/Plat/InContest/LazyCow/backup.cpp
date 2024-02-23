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
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int M = 1e6, modval = 1e9 + 7;

int n;
ll ans = 0;
set<simps> s;

simps getval(simps cur) {
    return {cur.second / cur.first, (cur.second % cur.first ? cur.second % cur.first : )};
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        simps cur;
        cin >> cur.first >> cur.second;
        auto it = s.ub(cur);
        if (it != s.end() and getval(*it) > getval(cur)) {
            cout << ans << "\n";
            continue;
        }
        s.insert(cur);
        it = s.lb(cur);
        while (it != s.begin()) {
            it--;
            if (getval(*it) > getval(cur)) break;
            s.erase(it);
            it = s.lb(cur);
        }
    }
	return 0;
}
