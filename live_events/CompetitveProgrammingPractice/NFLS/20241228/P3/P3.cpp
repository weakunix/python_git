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

const int N = 18;

int h, w, a, b;
ll ans = 0;
bool blocked[N][N];

void dfs(int r, int c, int cnt) {
    if (cnt > a) return;
    if (r == h and c == w) {
        ans += (cnt == a);
        return;
    }

    int newr = r, newc = c + 1;
    if (newc > w) {
        newr++;
        newc = 1;
    }
    dfs(newr, newc, cnt);
    if (not blocked[r][c] and not blocked[r + 1][c]) {
        blocked[r][c] = true;
        blocked[r + 1][c] = true;
        dfs(newr, newc, cnt + 1);
        blocked[r][c] = false;
        blocked[r + 1][c] = false;
    }
    if (not blocked[r][c] and not blocked[r][c + 1]) {
        blocked[r][c] = true;
        blocked[r][c + 1] = true;
        dfs(newr, newc, cnt + 1);
        blocked[r][c] = false;
        blocked[r][c + 1] = false;
    }

    return;
}

int main() {
    clr(blocked, true);

    cin >> h >> w >> a >> b;
    for (int i = 1; i <= h; i++) for (int j = 1; j <= w; j++) blocked[i][j] = false;

    dfs(1, 1, 0);
    cout << ans << "\n";

	return 0;
}
