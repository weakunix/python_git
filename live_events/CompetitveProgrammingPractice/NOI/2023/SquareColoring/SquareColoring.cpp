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

struct Query {
    int t, st, en, loc;

    Query() : t(-1), st(-1), en(-1), loc(-1) {}

    Query(int T, int St, int En, int Loc) : t(T), st(St), en(En), loc(Loc) {}

    ~Query() {}
};

bool operator<(Query a, Query b) {
    return (a.st == b.st ? a.en < b.en : a.st < b.st);
}

int n, m, q, k;
ll ans = 0;
vector<int> seg;
vector<Query> arr;
vector<vector<int>> add, rem, diag;
vector<vector<simps>> rng[2];

void processdiag() {
    bool go = true;
    while (go) {
        go = false;
        for (int i = 0; i < diag.size(); i++) {
            for (int j = i + 1; j < diag.size(); j++) {
                vector<int> a = diag[i], b = diag[j];
                if (a[0] > b[0]) swap(a, b);
                if ((a[0] - a[1] == b[0] - b[1]) and a[2] >= b[0]) {
                    diag.erase(diag.begin() + i);
                    diag.erase(diag.begin() + j - 1);
                    diag.pb({a[0], a[1], max(a[2], b[2]), max(a[3], b[3])});
                    go = true;
                    break;
                }
            }
            if (go) break;
        }
    }

    set<simps> dupl;
    for (vector<int>& v : diag) {
        ans += v[2] - v[0] + 1;
        for (Query& u : arr) {
            if (u.t == 0) {
                if (v[1] <= u.loc and v[3] >= u.loc) {
                    int x = u.loc + v[0] - v[1];
                    if (x >= u.st and x <= u.en) dupl.insert({x, u.loc});
                }
            }
            else {
                if (v[0] <= u.loc and v[2] >= u.loc) {
                    int y = u.loc + v[1] - v[0];
                    if (y >= u.st and y <= u.en) dupl.insert({u.loc, y});
                }
            }
        }
    }

    ans -= dupl.size();

    return;
}

void comp() {
    sort(all(arr));

    vector<int> og;
    set<int> allnums;
    map<int, int> mp;
    
    for (int i = 0; i < arr.size(); i++) {
        allnums.insert(arr[i].st);
        allnums.insert(arr[i].en);
        allnums.insert(arr[i].loc);
    }

    k = allnums.size();
    for (int i : allnums) {
        og.pb(i);
        mp[i] = mp.size();
    }

    rng[0].resize(k);
    rng[1].resize(k);
    for (int i = 0; i < arr.size(); i++) {
        arr[i].st = mp[arr[i].st];
        arr[i].en = mp[arr[i].en];
        arr[i].loc = mp[arr[i].loc];
        
        vector<simps>& cur = rng[arr[i].t][arr[i].loc];
        if (cur.size() and arr[i].st <= cur.back().second) setmx(cur.back().second, arr[i].en);
        else cur.pb({arr[i].st, arr[i].en});
    }

    for (int i = 0; i < 2; i++) for (int j = 0; j < k; j++) for (simps& s : rng[i][j]) ans += og[s.second] - og[s.first] + 1;

    add.resize(k);
    rem.resize(k);
    for (int i = 0; i < k; i++) {
        for (simps& s : rng[0][i]) {
            add[s.first].pb(i);
            rem[s.second].pb(i);
        }
    }

    return;
}

void setseg(int node, int l, int r, int idx, int change) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] += change;
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, change);
    setseg(2 * node + 1, mid + 1, r, idx, change);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

int getseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return getseg(2 * node, l, mid, a, b) + getseg(2 * node + 1, mid + 1, r, a, b);
}

int main() {
    cin >> n >> n >> m >> q;

    for (int i = 0; i < q; i++) {
        int t, a, b, c, d;
        cin >> t >> a >> b >> c >> d;
        t--;

        if (t == 0) arr.pb(Query(0, min(a, c), max(a, c), b));
        else if (t == 1) arr.pb(Query(1, min(b, d), max(b, d), a));
        else diag.pb({a, b, c, d});
    }

    processdiag();

    comp();

    seg.resize(4 * k);

    for (int i = 0; i < k; i++) {
        for (int j : add[i]) setseg(1, 0, k - 1, j, 1);
        for (simps& s : rng[1][i]) ans -= getseg(1, 0, k - 1, s.first, s.second);
        for (int j : rem[i]) setseg(1, 0, k - 1, j, -1);
    }

    cout << ans << "\n";

	return 0;
}
