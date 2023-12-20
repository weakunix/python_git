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

const int N = 2e5;

int n, segmx[4 * N], segmn[4 * N], lz[4 * N];

void prop(int node, int l, int r) {
    if (lz[node] == 0) return;
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    segmx[node] += lz[node];
    segmn[node] += lz[node];
    lz[node] = 0;
    return;
}

void setseg(int node, int l, int r, int a, int b, int c) {
    prop(node, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lz[node] += c;
        prop(node, l, r);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, a, b, c);
    setseg(2 * node + 1, mid + 1, r, a, b, c);
    segmn[node] = min(segmn[2 * node], segmn[2 * node + 1]);
    segmx[node] = max(segmx[2 * node], segmx[2 * node + 1]);
    return;
}

int main() {
    memset(segmx, 0, sizeof(segmx));
    memset(segmn, 0, sizeof(segmn));
    memset(lz, 0, sizeof(lz));

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        setseg(1, 0, n - 1, 0, a - 1, b == 1 ? -1 : 1);
        prop(1, 0, n - 1);
        if (segmx[1] <= 0) cout << ">\n";
        else if (segmn[1] >= 0) cout << "<\n";
        else cout << "?\n";
    }

	return 0;
}
