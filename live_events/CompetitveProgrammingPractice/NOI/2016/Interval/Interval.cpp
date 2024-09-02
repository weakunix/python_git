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

const int N = 5e5;

int n, m, ans = 2e9, seg[8 * N], lz[8 * N];
threesome arr[N];
set<int> allv;
unordered_map<int, int> comp;

void prop(int node, int l, int r) {
    if (not lz[node]) return;
    if (l < r) {
        lz[2 * node] += lz[node];
        lz[2 * node + 1] += lz[node];
    }
    seg[node] += lz[node];
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
    seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    return;
}

int main() {
    clr(seg, 0);
    clr(lz, 0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = {b - a + 1, {a, b}};
        allv.insert(a);
        allv.insert(b);
    }

    for (int i : allv) comp[i] = comp.size();
    sort(arr, arr + n);

    int l = 0, r = 0;
    while (r < n or seg[1] >= m) {
        int a, b, c;
        if (seg[1] >= m) {
            a = comp[arr[l].sec];
            b = comp[arr[l].third];
            c = -1;
            l++;
        }
        else {
            a = comp[arr[r].sec];
            b = comp[arr[r].third];
            c = 1;
            r++;
        }
        setseg(1, 0, comp.size() - 1, a, b, c);
        if (seg[1] >= m) setmn(ans, arr[r - 1].first - arr[l].first);
    }

    cout << (ans == 2e9 ? -1 : ans) << "\n";

	return 0;
}
