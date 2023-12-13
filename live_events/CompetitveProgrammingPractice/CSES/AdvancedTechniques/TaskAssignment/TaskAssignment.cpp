#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <map>
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

const int N = 402;

int n, w[N][N], best[N], prv[N], ans = 0, ansedge[N];
bool cap[N][N], vis[N];
vector<int> adj[N];

int main() {
    memset(w, 0, sizeof(w));
    memset(cap, false, sizeof(cap));
    memset(vis, false, sizeof(vis));

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cur;
            cin >> cur;
            w[i][j + n] = cur;
            w[j + n][i] = -cur;
            cap[i][j + n] = true;
            adj[i].push_back(j + n);
            adj[j + n].push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        cap[2 * n][i] = true;
        cap[i + n][2 * n + 1] = true;
        adj[2 * n].push_back(i);
        adj[i].push_back(2 * n);
        adj[i + n].push_back(2 * n + 1);
        adj[2 * n + 1].push_back(i + n);
    }

    for (int i = 0; i < n; i++) {
        fill(best, best + N, 1e9);
        best[2 * n] = 0;
        queue<int> q;
        q.push(2 * n);
        vis[2 * n] = true;

        while (not q.empty()) {
            int node = q.front();
            q.pop();
            vis[node] = false;

            for (int i : adj[node]) {
                if (not cap[node][i]) continue;
                if (best[node] + w[node][i] < best[i]) {
                    best[i] = best[node] + w[node][i];
                    prv[i] = node;
                    if (not vis[i]) {
                        vis[i] = true;
                        q.push(i);
                    }
                }
            }
        }

        int node = 2 * n + 1;
        vector<int> stck;
        while (node != 2 * n) {
            stck.push_back(node);

            int p = prv[node];
            ans += w[p][node];
            cap[p][node] = false;
            cap[node][p] = true;
            node = p;
        }

        for (int i = 1; i < stck.size(); i += 2) ansedge[stck[i + 1]] = stck[i] - n;
    }

    cout << ans << "\n";
    for (int i = 0; i < n; i++) cout << i + 1 << " " << ansedge[i] + 1 << "\n";

	return 0;
}
