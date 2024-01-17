#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 1e5, modval = 1e9 + 7;

struct Block {
    int u, l, r, s;

    Block(int uu = 0, int lll = 0, int rr = 0, int ss = 0) {
        u = uu;
        l = lll;
        r = rr;
        s = ss;
        return;
    }
};

bool operator<(Block a, Block b) {
    return a.u < b.u;
}

int h, w, n, nxtl[N], nxtr[N];
ll dp[N], ans = 0;
bool rem[N];
priority_queue<int> seg[4 * N];
Block block[N];

void setseg(int node, int l, int r, int a, int b, int c) {
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        seg[node].push(c);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, c);
    setseg(2 * node + 1, mid + 1, r, a, b, c);
    return;
}

int getseg(int node, int l, int r, int idx) {
    if (l > idx or r < idx) return -1;
    while (seg[node].size() and rem[seg[node].top()]) seg[node].pop();
    int res = (seg[node].size() ? seg[node].top() : -1);
    if (l < r) {
        int mid = l + (r - l) / 2;
        setmx(res, max(getseg(2 * node, l, mid, idx), getseg(2 * node + 1, mid + 1, r, idx)));
    }
    return res;
}

ll calc(int y) {
    if (y == -1) return 1;

    if (dp[y] != -1) return dp[y];
    ll resl, resr;
    
    if (block[y].l > 0) resl = calc(nxtl[y]);
    if (block[y].r < w - 1) resr = calc(nxtr[y]);

    if (block[y].l == 0) dp[y] = 2 * resr;
    else if (block[y].r == w - 1) dp[y] = 2 * resl;
    else dp[y] = resl + resr;
    dp[y] %= modval;
    return dp[y];
}

int main() {
    //freopen("fall.in", "r", stdin);
    //freopen("fall.out", "w", stdout);
    
    memset(dp, -1, sizeof(dp));
    memset(rem, false, sizeof(rem));

    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        cin >> block[i].u >> block[i].l >> block[i].r >> block[i].s;
        block[i].l--; block[i].r--;
    }
    sort(block, block + n);

    priority_queue<simps, vector<simps>, greater<simps>> pq;
    for (int i = 0; i < n; i++) {
        while (pq.size() and pq.top().first < block[i].u) {
            rem[pq.top().second] = true;
            pq.pop();
        }

        if (block[i].l > 0) nxtl[i] = getseg(1, 0, w - 1, block[i].l - 1);
        if (block[i].r < w - 1) nxtr[i] = getseg(1, 0, w - 1, block[i].r + 1);

        setseg(1, 0, w - 1, block[i].l, block[i].r, i);
        pq.push({block[i].u + block[i].s, i});
    }

    while (pq.size() and pq.top().first <= h) {
            rem[pq.top().second] = true;
            pq.pop();
    }

    for (int i = 0; i < w; i++) {
        int cur = getseg(1, 0, w - 1, i);
        if (cur == -1) ans++;
        else ans = (ans + calc(cur)) % modval;
    }
    cout << ans << "\n";

	return 0;
}
