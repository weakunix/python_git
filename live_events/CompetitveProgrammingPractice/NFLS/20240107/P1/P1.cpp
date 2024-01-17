#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 1e5, L = 17;

int n, q, time = 0, st[N], en[N], par[L][N], ht[N], curq[N];
simps vpar[N];
vector<int> adj[N];
vector<simps> vadj[N];

bool cmp(int a, int b) {
    return en[a] < en[b];
}

void dfs(int node, int parent, int height) {
    par[node] = parent;
    ht[node] = height;
    st[node] = time;
    time++;
    for (int i : adj[node]) if (i != parent) dfs(i, node, height + 1);
    en[node] = time;
    time++;
    return;
}

int getpar(int node, int k) {
    int cnt = 0;
    while (k) {
        if (k & 1) node = par[cnt][node];
        k >>= 1;
        cnt++;
    }
    return node;
}

int getlca(int a, int b) {
    if (ht[a] < ht[b]) swap(a, b);
    a = getpar(a, ht[a] - ht[b]);
    if (a == b) return a;
    for (int i = L - 1; i >= 0; i--) {
        if (par[i][a] != par[i][b]) {
            a = par[i][a];
            b = par[i][b];
        }
    }
    return par[0][a];
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1, 0);
    for (int i = 1; i < L; i++) for (int j = 0; j < n; j++) par[i][j] = (par[i - 1][j] == -1 ? -1 : par[i - 1][par[i - 1][j]]);

    for (int i = 0; i < q; i++) {
        int k;
        vector<int> vtree;
        cin >> k;
        for (int j = 0; j < k; j++) cin >> curq[j];
        sort(curq, curq + k, cmp);
       
        vector<int> stck = {curq[0]};
        vtree.push_back(curq[0]);
        for (int j = 1; j < k; j++) {
            int cur = curq[i], l = getlca(curq[i - 1], cur);
        }
    }

	return 0;
}
