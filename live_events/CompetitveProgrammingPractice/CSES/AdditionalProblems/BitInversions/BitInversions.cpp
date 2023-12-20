#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 2e5;

struct Node {
    int pfx, sfx, mx;
};

int n, m;
Node seg[2][4 * N];
string s;

void initseg(int node, int l, int r) {
    seg[0][node].pfx = r - l + 1;
    seg[0][node].sfx = r - l + 1;
    seg[0][node].mx = r - l + 1;
    seg[1][node].pfx = 0;
    seg[1][node].sfx = 0;
    seg[1][node].mx = 0;

    if (l == r) return;

    int mid = l + (r - l) / 2;
    initseg(2 * node, l, mid);
    initseg(2 * node + 1, mid + 1, r);

    return;
}

void setseg(int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[val][node].pfx = 1;
        seg[val][node].sfx = 1;
        seg[val][node].mx = 1;
        seg[1 - val][node].pfx = 0;
        seg[1 - val][node].sfx = 0;
        seg[1 - val][node].mx = 0;
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, val);
    setseg(2 * node + 1, mid + 1, r, idx, val);
    for (int i = 0; i < 2; i++) {
        seg[i][node].pfx = seg[i][2 * node].pfx + (seg[i][2 * node].pfx == mid - l + 1 ? seg[i][2 * node + 1].pfx : 0);
        seg[i][node].sfx = seg[i][2 * node + 1].sfx + (seg[i][2 * node + 1].sfx == r - mid ? seg[i][2 * node].sfx : 0);
        seg[i][node].mx = max({seg[i][2 * node].mx, seg[i][2 * node + 1].mx, seg[i][2 * node].sfx + seg[i][2 * node + 1].pfx});
    }
    return;
}

int main() {
    cin >> s >> m;
    n = s.size();

    initseg(1, 0, n - 1);
    for (int i = 0; i < n; i++) if (s[i] == '1') setseg(1, 0, n - 1, i, 1);

    for (int i = 0; i < m; i++) {
        int idx;
        cin >> idx;
        idx--;

        if (s[idx] == '0') {
            setseg(1, 0, n - 1, idx, 1);
            s[idx] = '1';
        }
        else {
            setseg(1, 0, n - 1, idx, 0);
            s[idx] = '0';
        }

        cout << max(seg[0][1].mx, seg[1][1].mx) << " ";
    }

    cout << "\n";

	return 0;
}
