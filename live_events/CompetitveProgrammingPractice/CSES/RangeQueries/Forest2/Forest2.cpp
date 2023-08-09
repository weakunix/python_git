#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
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

int n, q;
vector<vector<int>> bit;
vector<vector<bool>> arr;

void set(int x, int y) {
    int change = arr[y][x] ? -1 : 1;
    arr[y][x] = not arr[y][x];
    for (; y <= n; y += y & (-y)) {
        for (int curx = x; curx <= n; curx += curx & (-curx)) bit[y][curx] += change;
    }
    return;
}

int get(int x, int y) {
    int res = 0;
    for (; y > 0; y ^= y & (-y)) {
        for (int curx = x; curx > 0; curx ^= curx & (-curx)) res += bit[y][curx];
    }
    return res;
}

int main() {
    cin >> n >> q;
    bit.resize(n + 1, vector<int>(n + 1));
    arr.resize(n + 1, vector<bool>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '*') set(j, i);
        }
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> y >> x;
            set(x, y);
            continue;
        }
        int x1, x2, y1, y2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1) << "\n";
    }
	return 0;
}
