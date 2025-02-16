#include <iostream>
#include <cstdio>
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
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 2e5, C = 60;

int n, k;
ll m, a[N], ops[N], ans = 0;

ll getneeded(ll num, int bit) {
    ll cur = (1ll << bit);
    if (num & cur) return 0;
    return cur - num % cur;
}

int main() {
    clr(ops, 0);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = C; i >= 0; i--) {
        sort(a, a + n);
        
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (int j = 0; j < n; j++) pq.push(ops[j] + getneeded(a[j], i));

        ll req = 0;
        for (int j = 0; j < k; j++) {
            req += pq.top();
            pq.pop();
            if (req > m) break;
        }
        
        if (req > m) continue;

        ans |= (1ll << i);
        for (int j = 0; j < n; j++) {
            ll cur = getneeded(a[j], i);
            ops[j] += cur;
            a[j] += cur;
        }
    }

    cout << ans << "\n";

	return 0;
}
