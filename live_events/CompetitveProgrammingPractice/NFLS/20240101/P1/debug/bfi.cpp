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

const int N = 1001, modval = 1e9 + 7;

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

int h, w, n;
ll dp[N][N], ans = 0;
Block block[N];

ll calc(int x, int yidx) {
    if (dp[x][yidx] != -1) return dp[x][yidx];

    int y = (yidx == n ? h + 1 : block[yidx].u);
    for (int i = yidx - 1; i >= 0; i--) {
        if (block[i].l > x or block[i].r < x) continue;
        if (y > block[i].u + block[i].s) continue;

        if (block[i].l == 1) dp[x][yidx] = 2 * calc(block[i].r + 1, i);
        else if (block[i].r == w) dp[x][yidx] = 2 * calc(block[i].l - 1, i);
        else dp[x][yidx] = calc(block[i].l - 1, i) + calc(block[i].r + 1, i);
        dp[x][yidx] %= modval;
        return dp[x][yidx];
    }
    
    dp[x][yidx] = 1;
    return 1; 
}

int main() {
    //freopen("fall.in", "r", stdin);
    //freopen("fall.out", "w", stdout);

    memset(dp, -1, sizeof(dp));

    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) cin >> block[i].u >> block[i].l >> block[i].r >> block[i].s;
    sort(block, block + n);

    for (int i = 1; i <= w; i++) ans = (ans + calc(i, n)) % modval;
    cout << ans << "\n";

	return 0;
}
