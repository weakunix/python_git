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

const int modval = 1e9 + 7, dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};

int t;

void subcase() {
    int n, m;
    ll ans = 1;
    vector<simps> imp;
    vector<vector<bool>> grid;

    cin >> n >> m;
    grid.resize(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            grid[i][j] = (c != '#');
            if (c == 'o') imp.pb({i, j});
        }
    }

    for (simps& s : imp) {
        int ud = 0, lr = 0;
        for (int i = 0; i < 4; i++) {
            int a = s.first + dirx[i], b = s.second + diry[i];
            if ((a < 0 or a >= n) or (b < 0 or b >= m)) continue;
            if (not grid[a][b]) continue;
            if (i % 2) ud++;
            else lr++;
        }
        ans *= ud * lr;
        ans %= modval;
    }
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
