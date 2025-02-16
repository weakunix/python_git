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

const int N = 4, M = 12, dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};

int n, w, h, lim, x[N], y[N], tarx, tary;
bool grid[M][M];
map<int, int> seen;

int comp() {
    int res = 0;
    for (int i = n - 1; i >= 0; i--) res = res * 100 + (y[i] - 1) * 10 + (x[i] - 1);
    return res;
}
void uncomp(int cur) {
    for (int i = 0; i < n; i++) {
        x[i] = cur % 10 + 1;
        cur /= 10;
        y[i] = cur % 10 + 1;
        cur /= 10;
    }
    return;
}

void resetbot() {
    for (int i = 0; i < n; i++) grid[x[i]][y[i]] = true;
    return;
}

void loadbot() {
    for (int i = 0; i < n; i++) grid[x[i]][y[i]] = false;
    return;
}

int main() {
    clr(grid, false);

    cin >> n >> w >> h >> lim;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            char c;
            cin >> c;
            if (c == 'W') continue;
            grid[i][j] = true;
            if (c == '.') continue;
            if (c == 'X') {
                tarx = i;
                tary = j;
                continue;
            }
            grid[i][j] = false;
            x[c - '1'] = i;
            y[c - '1'] = j;
        }
    }

    queue<int> q;
    q.push(comp());
    seen[comp()] = 0;

    while (q.size()) {
        int cur = q.front(), moves = seen[cur];
        q.pop();

        resetbot();
        uncomp(cur);
        loadbot();

        if (x[0] == tarx and y[0] == tary) {
            cout << moves << "\n";
            return 0;
        }
        if (moves == lim) continue;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                int curx = x[i], cury = y[i];
                while (grid[curx + dirx[j]][cury + diry[j]]) {
                    curx += dirx[j];
                    cury += diry[j];
                }
                x[i] = curx;
                y[i] = cury;
                if (not seen.count(comp())) {
                    q.push(comp());
                    seen[comp()] = moves + 1;
                }
                uncomp(cur);
            }
        }
    }

    cout << "NO SOLUTION\n";
    
	return 0;
}
