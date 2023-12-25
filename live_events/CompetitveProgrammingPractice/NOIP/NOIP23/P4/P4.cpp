#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
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

const int M = 1e5;

int t, n, m, k, d, s, prvloc, idx[M];
ll seg[4 * M], lz[4 * M], ans;
threesome arr[M];
set<int> allt;
map<int, int> comp;

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

void setseg(int node, int l, int r, int a, int b, ll c) {
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

ll getseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return -1e18;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return max(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

void subcase() {
    prvloc = 0;
    ans = 0;
    memset(seg, 0, sizeof(seg));
    memset(lz, 0, sizeof(lz));
    allt.clear();
    comp.clear();

    cin >> n >> m >> k >> d;
    for (int i = 0; i < m; i++) {
        cin >> arr[i].first >> arr[i].sec >> arr[i].third;
        allt.insert(arr[i].first - arr[i].sec + 1);
    }
    s = allt.size();
    sort(arr, arr + m);

    for (int i : allt) {
        int cur = comp.size();
        comp[i] = cur;
        idx[cur] = i;
        setseg(1, 0, s - 1, cur, cur, (ll) d * (i - 1));
    }

    for (int i = 0; i < m; i++) {
        arr[i].sec = comp[arr[i].first - arr[i].sec + 1];
        setseg(1, 0, s - 1, 0, arr[i].sec, arr[i].third);

        if (i < m - 1 and arr[i + 1].first == arr[i].first) continue;

        setseg(1, 0, s - 1, 0, s - 1, (ll) d * (prvloc - arr[i].first));
        prvloc = arr[i].first;
        
        ll cur = getseg(1, 0, s - 1, lower_bound(idx, idx + s, arr[i].first - k + 1) - idx, upper_bound(idx, idx + s, arr[i].first) - idx - 1);

        if (cur > ans) {
            setseg(1, 0, s - 1, lower_bound(idx, idx + s, arr[i].first + 2) - idx, s - 1, cur - ans);
            ans = cur;
        }
    }
    
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    //freopen("run.in", "r", stdin);
    //freopen("run.out", "w", stdout);

	cin >> t >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
