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

const int N = 1002, M = 1002, modval = 998244353;

int t, n, m, c, f, rt[N][M];
ll ansc, ansf;
bool grid[N][M];

void subcase() {
    ansc = 0;
    ansf = 0;

    clr(grid, true);
    clr(rt, 0);

    cin >> n >> m >> c >> f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            grid[i][j] = (c == '1');
        }
    }

    for (int i = 1; i <= n; i++) for (int j = m; j > 0; j--) if (not grid[i][j]) rt[i][j] = rt[i][j + 1] + 1;

    for (int j = 1; j <= m; j++) {
        ll cnt = 0, curc = 0, curf = 0, nxtc = 0, nxtf = 0;
        for (int i = n; i > 0; i--) {
            if (grid[i][j]) {
                cnt = 0;
                curc = 0;
                curf = 0;
                nxtc = 0;
                nxtf = 0;
                continue;
            }
            ansc = (ansc + curc * (rt[i][j] - 1)) % modval;
            ansf = (ansf + curf * (rt[i][j] - 1)) % modval;
            curc = nxtc;
            curf = nxtf;
            nxtc = (nxtc + rt[i][j] - 1) % modval;
            nxtf = (nxtf + (rt[i][j] - 1) * cnt) % modval;
            cnt++;
        }
    }

    cout << ansc * c << " " << ansf * f << "\n";

	return;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);
	cin >> t >> n;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
