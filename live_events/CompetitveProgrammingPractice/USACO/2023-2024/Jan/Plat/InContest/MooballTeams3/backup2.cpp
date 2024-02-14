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

const int N = 2e5 + 1, modval = 1e9 + 7;

int n, getx[N], gety[N], bit[N], seg[4 * N], lz[4 * N];
simps pts[N];
ll pw[N], ans = 0;

void setbit(int idx) {
    for (; idx <= n; idx += idx & (-idx)) bit[idx]++;
    return;
}

int getbit(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

void prop(int node, int l, int r) {
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    seg[node] += lz[node] * (r - l + 1);
}

void setseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
}

int getseg(int node, int l, int r, int idx) {
    ;
}

void solve() {
    for (int i = 0; i < n; i++) {
        getx[pts[i].second] = pts[i].first;
        gety[pts[i].first] = pts[i].second;
    }

    for (int x = 1; x <= n; x++) {
        int y = gety[x];
        ans = (ans + pw[x - 1] * (pw[n - x] - 1)) % modval;
    }

    clr(bit, 0);
    clr(seg, 0);
    clr(lz, 0);

    for (int y = 1; y <= n; y++) {
        int x = getx[y];
        setbit(x);

        int cur = getbit(x);

        ans = (ans + modval - pw[cur - 1] * (pw[n - cur] - 1) % modval) % modval;

        
    }
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = 2 * pw[i - 1] % modval;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    solve();
    for (int i = 0; i < n; i++) pts[i] = {n - pts[i].second + 1, pts[i].first};
    solve();

    cout << 2 * ans % modval << "\n";

	return 0;
}
