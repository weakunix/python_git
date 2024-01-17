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

const int N = 1e5, Q = 1e5;

int n, q, sz[N], ans[Q];
bool vis[N];
vector<int> adj[N];
queue<threesome> ord;

int dfs(int node, int parent) {
    sz[node] = 1;
    for (int i : adj[node]) if (not vis[i] and i != parent) sz[node] += dfs(i, node);
    return sz[node];
}

int findcent(int node) {
    int cur = dfs(node, -1), parent = -1;
    bool done = false;
    while (not done) {
        done = true;
        for (int i : adj[node]) {
            if (vis[i] or i == parent) continue;
            if (sz[i] * 2 > cur) {
                node = i;
                done = false;
                break;
            }
        }
    }
    return node;
}

int main() {
    memset(ans, 0, sizeof(ans));
    memset(vis, false, sizeof(vis));

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int cur;
            cin >> cur;
            cur--;
            //TODO INSERT CUR
        }
    }

    ord.push({0, {-1, 1e9}}); //TODO REVISIT

    while (ord.size()) {
        int node = ord.front().first, prvcent = ord.front().sec, prvdist = ord.front().third;
        ord.pop();

        node = findcent(node);
    }

	return 0;
}
