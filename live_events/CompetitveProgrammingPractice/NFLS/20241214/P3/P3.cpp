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

const int S = 18, dirr[4] = {1, 0, -1, 0}, dirc[4] = {0, 1, 0, -1};

int n, m, ans = -1;
bool vis[S][S];

void dfs(int r, int c, int str, int stc, int dist) {
    vis[r][c] = true;
    for (int i = 0; i < 4; i++) {
        int newr = r + dirr[i], newc = c + dirc[i];
        if ((newr == str and newc == stc) and dist > 2) setmx(ans, dist);
        if (vis[newr][newc]) continue;
        dfs(newr, newc, str, stc, dist + 1);
    }
    vis[r][c] = false;
    return;
}

int main() {
    clr(vis, true);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            vis[i][j] = (c == '#');
        }
    }

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) if (not vis[i][j]) dfs(i, j, i, j, 1);

    cout << ans << "\n";

	return 0;
}
