#include <iostream>
#include <cstdio>
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

const int N = 1e5;

int n, seg[4 * N];
vector<int> yvals[N];

void getpts() {
     int loc[N];

    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cur--;
        loc[cur] = i;
    }

    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cur--;
        for (int j = max(cur - 4, 0); j <= min(cur + 4, n - 1); j++) yvals[loc[j]].push_back(i);
    }
}

void setseg(int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] = max(val, seg[node]);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, val);
    setseg(2 * node + 1, mid + 1, r, idx, val);
    seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    return;
}

int getseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return max(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);

    memset(seg, 0, sizeof(seg));

    cin >> n;
    getpts();

    for (int i = 0; i < n; i++) {
        for (int j = yvals[i].size() - 1; j >= 0; j--) {
            int cur = yvals[i][j];
            setseg(1, 0, n - 1, cur, getseg(1, 0, n - 1, 0, cur - 1) + 1);
        }
    }

    cout << getseg(1, 0, n - 1, 0, n - 1) << "\n";

	return 0;
}
