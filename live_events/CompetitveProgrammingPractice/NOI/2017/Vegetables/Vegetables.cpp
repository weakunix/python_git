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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 1, M = 10;

int n, m, q, par[N], rem[N];
ll a[N], s[N], c[N], x[N], ans[N * M];
priority_queue<simps> pq;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

int main() {
    clr(par, -1);

    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> s[i] >> c[i] >> x[i];
        if (c[i] > 0) pq.push({a[i] + s[i], i});
    }

    fill(rem + 1, rem + N, m);

    int cntr = 0;
    while (pq.size()) {
        int idx = pq.top().second;
        ll price = pq.top().first;
        pq.pop();

        int day;
        if (x[idx] == 0) day = N - 1;
        else day = min((c[idx] - 1) / x[idx] + 1, (ll) N - 1);
        day = getpar(day);

        if (day == 0) continue;

        cntr++;
        ans[cntr] = ans[cntr - 1] + price;

        c[idx]--;
        if (c[idx] > 0) pq.push({a[idx], idx});

        rem[day]--;
        if (rem[day] == 0) par[day] = getpar(day - 1);
    }

    for (int i = 0; i < q; i++) {
        int cur;
        cin >> cur;
        cout << ans[min(cur * m, cntr)] << "\n";
    }

	return 0;
}
