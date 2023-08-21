#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")

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

int n, q, cnt = 0, arr[N], par[N], ht[N], hv[N], et[N], tp[N], idx[N], lg[2 * N], seg[4 * N];
simps sparse[20][2 * N];
vector<vector<int>> adj;

int dfs1(int node) {
    int mx = 0, sub = 1;
    et[node] = cnt;
    sparse[0][cnt] ={ht[node], node};
    cnt++;
    for (int i : adj[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        ht[i] = ht[node] + 1;
        int cur = dfs1(i);
        sparse[0][cnt] ={ht[node], node};
        cnt++;
        sub += cur;
        if (cur > mx) hv[node] = i;
        mx = max(cur, mx);
    }
    return sub;
}

void dfs2(int node, int top) {
    tp[node] = top;
    idx[node] = cnt;
    cnt++;
    if (hv[node] != -1) dfs2(hv[node], top);
    for (int i : adj[node]) {
        if (i != par[node] and i != hv[node]) dfs2(i, i);
    }
    return;
}

int getmin(int a, int b) {
    a = et[a]; b = et[b];
    if (a > b) swap(a, b);
    int len = lg[b - a + 1];
    return min(sparse[len][a], sparse[len][b - (1 << len) + 1]).second;
}

void set(int node, int l, int r, int k, int val) {
    if (l > k or r < k) return;
    if (l == r) {
        seg[node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    set(2 * node, l, mid, k, val);
    set(2 * node + 1, mid + 1, r, k, val);
    seg[node] = max(seg[2 * node], seg[2 * node + 1]);
    return;
}

int get(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return max(get(2 * node, l, mid, a, b), get(2 * node + 1, mid + 1, r, a, b));
}

int calcpath(int st, int en) {
    int res = 0;
    while (st != -1 and ht[st] >= ht[en]) {
        if (st == tp[st]) {
            res = max(arr[st], res);
            st = par[st];
            continue;
        }
        int curtp = tp[st];
        if (ht[curtp] < ht[en]) curtp = en;
        res = max(get(1, 0, n - 1, idx[curtp], idx[st]), res);
        st = par[curtp];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    par[0] = -1;
    ht[0] = 0;
    memset(hv, -1, sizeof(hv));
    memset(seg, 0, sizeof(seg));
    lg[1] = 0;

    cin >> n >> q;
    adj.resize(n);
    for (int i = 2; i < 2 * n; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(0);
    assert(cnt == 2 * n - 1);
    cnt = 0;
    dfs2(0, 0);
    for (int i = 1; (1 << i) < 2 * n; i++) {
        for (int j = 0; j + (1 << i) < 2 * n; j++) sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
    }
    for (int i = 0; i < n; i++) set(1, 0, n - 1, idx[i], arr[i]);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            set(1, 0, n - 1, idx[s], x);
            arr[s] = x;
        }
        else {
            int a, b, l;
            cin >> a >> b;
            a--; b--;
            l = getmin(a, b);
            cout << max(calcpath(a, l), calcpath(b, l)) << " ";
        }
    }
    cout << "\n";
	return 0;
}
