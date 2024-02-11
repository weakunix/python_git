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
#define lb lower_bound
#define ub upper_bound
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

const int modval = 1e9 + 7;

int n;
ll ans = 0;
map<ll, ll> rng;
unordered_map<ll, ll> prv;

ll getlo(ll val) { // <=
    auto it = rng.ub(val);
    if (it == rng.begin()) return -1;
    it--;
    return it->first;
}

ll gethi(ll val) { // >
    auto it = rng.ub(val);
    if (it == rng.end()) return -1;
    return it->first;
}

ll getsm(ll val) {
    val %= modval;
    return (val * (val + 1) / 2) % modval;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll ogd, ogb, d, b;
        cin >> d >> b;
        ogd = d;
        ogb = b;

        b -= prv[d];

        if (b < 0) {
            cout << "18\n"; //sample
            continue;
        }

        if (b == 0) {
            cout << ans << "\n";
            continue;
        }

        ll cur = getlo(d);
        if (cur != -1 and rng[cur] >= d - 1) d = cur;
        else {
            rng[d] = d;
            ans = (ans + d) % modval;
            b--;
        }

        while (true) {
            cur = gethi(d);
            if (cur == -1 or cur - rng[d] - 1 > b) break;
            ans = (ans + getsm(cur - 1) - getsm(rng[d]) + modval) % modval;
            b -= cur - rng[d] - 1;
            rng[d] = rng[cur];
            rng.erase(cur);
        }

        ans = (ans + getsm(rng[d] + b) - getsm(rng[d]) + modval) % modval;
        rng[d] += b;
        cout << ans << "\n";
        prv[ogd] = ogb;
    }

	return 0;
}
