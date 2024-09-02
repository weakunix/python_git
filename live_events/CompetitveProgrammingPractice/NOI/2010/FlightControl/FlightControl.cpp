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

int n, m, must[N], outdeg[N];
bool vis[N];
vector<int> adj[N], srt[N];
set<int> ord[N];

void dfs1(int node, int st) {
    vis[node] = true;
    if (node != st) {
        ord[node].insert(st);
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

void genans2(int node) {
    int cnt = -1 - (n - must[node]), idx = must[node];
    for (int i = must[node]; i <= n; i++) cnt += srt[i].size();
    while (cnt) {
        cnt--;
        idx--;
        for (int i : srt[idx]) cnt += (not ord[node].count(i));
    }
    cout << idx << " ";
    return;
}

int main() {
    clr(outdeg, 0);

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

    for (int i = 0; i < n; i++) srt[must[i]].pb(i);

    for (int i = 0; i < n; i++) genans2(i);
    cout << "\n";

	return 0;
}
