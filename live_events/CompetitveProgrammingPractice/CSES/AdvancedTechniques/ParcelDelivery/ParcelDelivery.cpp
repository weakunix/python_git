#include <iostream>
#include <cstring>
#include <vector>
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

const int N = 500, M = 2000;

int n, m, k, flow = 0, best[N], ans = 0;
simps prv[N];
threesome edges[M];
map<int, int> adj[N][N];

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int a, b, r, c;
        cin >> a >> b >> r >> c;
        a--; b--;
        adj[a][b][c] += r;
        edges[2 * i] = {a, {b, c}};
        edges[2 * i + 1] = {b, {a, -c}};
    }

    while (flow < k) {
        fill(best, best + n, 1e9);
        best[0] = 0;

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < 2 * m; j++) {
                int a = edges[j].first, b = edges[j].sec, c = edges[j].third;
                if (adj[a][b][c] == 0) continue;
                if (best[a] + c < best[b]) {
                    best[b] = best[a] + c;
                    prv[b] = {a, c};
                }
            }
        }

        if (best[n - 1] == 1e9) {
            cout << "-1\n";
            return 0;
        }


        int cur = k - flow, node = n - 1;
        while (node != 0) {
            int p = prv[node].first, c = prv[node].second;
            cur = min(adj[p][node][c], cur);
            node = p;
        }

        node = n - 1;
        while (node != 0) {
            int p = prv[node].first, c = prv[node].second;
            adj[p][node][c] -= cur;
            adj[node][p][-c] += cur;
            ans += cur * c;
            node = p;
        }
        flow += cur;
    }

    cout << ans << "\n";

	return 0;
}
