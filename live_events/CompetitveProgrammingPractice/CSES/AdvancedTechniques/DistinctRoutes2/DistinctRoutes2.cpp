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

const int N = 500, M = 1000;

int n, m, k, best[N], prv[N], ans = 0;
bool rev[M], works[N][N];
simps edges[M];
vector<int> adj[N], curans;

void dfs(int node) {
    curans.push_back(node);
    if (node == n - 1) return;
    for (int i : adj[node]) {
        if (works[node][i]) {
            works[node][i] = false;
            dfs(i);
            return;
        }
    }

    assert(false);

    return;
}

int main() {
    memset(rev, false, sizeof(rev));
    memset(works, false, sizeof(works));

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edges[i] = {a, b};
        adj[a].push_back(b);
    }

    for (int i = 0; i < k; i++) {
        fill(best, best + n, 1e9);
        best[0] = 0;
        for (int j = 0; j < n - 1; j++) {
            for (int l = 0; l < m; l++) {
                int a = edges[l].first, b = edges[l].second, w = rev[l] ? -1 : 1;
                if (rev[l]) swap(a, b);
                if (best[a] + w < best[b]) {
                    best[b] = best[a] + w;
                    prv[b] = l;
                }
            }
        }

        if (best[n - 1] == 1e9) {
            cout << "-1\n";
            return 0;
        }

        int node = n - 1;
        while (node != 0) {
            int e = prv[node], p = rev[e] ? edges[e].second : edges[e].first;
            ans += rev[e] ? -1 : 1;
            rev[e] = not rev[e];
            node = p;
        }
    }

    cout << ans << "\n";
    for (int i = 0; i < m; i++) if (rev[i]) works[edges[i].first][edges[i].second] = true;
    for (int i = 0; i < k; i++) {
        curans.clear();
        dfs(0);
        cout << curans.size() << "\n";
        for (int j : curans) cout << j + 1 << " ";
        cout << "\n";
    }

	return 0;
}
