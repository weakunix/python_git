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

const int N = 2001;

int n, m, must[N], outdeg[N], cnt[N], seg[4 * N], lz[4 * N];
bool vis[N];
vector<int> adj[N], ord[N];

bool cmp(int a, int b) {
    return must[a] > must[b];
}

void dfs1(int node, int st) {
    vis[node] = true;
    if (node != st) {
        ord[node].pb(st);
        outdeg[st]++;
    }
    for (int i : adj[node]) if (not vis[i]) dfs1(i, st);
    return;
}

void genans1() {
    priority_queue<simps> pq;
    for (int i = 0; i < n; i++) pq.push({-must[i], i});
    while (pq.size()) {
        cout << pq.top().second + 1 << " ";
        pq.pop();
    }
    cout << "\n";
    return;
}

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

void buildseg(int node, int l, int r) {
    lz[node] = 0;
    if (l == r) {
        seg[node] = cnt[l];
        return;
    }
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    seg[node] = min(seg[2 * node], seg[2 * node + 1]);
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
    seg[node] = min(seg[2 * node], seg[2 * node + 1]);
}

int getseg(int node, int l, int r, int a, int b) {
    prop(node, l, r);
    if (l > b or r < a) return 1e9;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return min(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

void genans2(int node) {
    buildseg(1, 1, n);

    ord[node].pb(node);
    sort(all(ord[node]), cmp);

    set<simps> s;
    for (int i = 0; i < n; i++) s.insert({must[i], i});
    
    int idx = 1;
    while (ord[node].size()) {
        int cur = ord[node].back();
        if (getseg(1, 1, n, idx, must[cur] - 1) == 0) cur = s.begin()->second;
        else ord[node].bp();
        s.erase({must[cur], cur});
        idx++;
        setseg(1, 1, n, idx, must[cur] - 1, -1);
    }

    cout << idx - 1 << " ";

    return;
}

int main() {
    clr(outdeg, 0);
    clr(cnt, 0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> must[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].pb(v);
    }

    for (int i = 0; i < n; i++) {
        clr(vis, false);
        dfs1(i, i);
    }

    queue<int> q;
    for (int i = 0; i < n; i++) if (not outdeg[i]) q.push(i);
    while (q.size()) {
        int node = q.front();
        q.pop();
        for (int j : ord[node]) {
            setmn(must[j], must[node] - 1);
            outdeg[j]--;
            if (not outdeg[j]) q.push(j);
        }
    }

    genans1();

    for (int i = 0; i < n; i++) cnt[must[i]]++;
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; i++) cnt[i] = i - cnt[i];
    
    for (int i = 0; i < n; i++) genans2(i);
    cout << "\n";

	return 0;
}
