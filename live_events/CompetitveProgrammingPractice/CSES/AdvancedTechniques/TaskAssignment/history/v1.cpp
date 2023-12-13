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

const int N = 402;

int n, w[N][N], best[N], prv[N], ans = 0, ansedge[N];
bool cap[N][N];
vector<simps> edges;

int main() {
    memset(w, 0, sizeof(w));
    memset(cap, false, sizeof(cap));

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int cur;
            cin >> cur;
            w[i][j + n] = cur;
            w[j + n][i] = -cur;
            cap[i][j + n] = true;
            edges.push_back({i, j + n});
            edges.push_back({j + n, i});
        }
    }
    for (int i = 0; i < n; i++) {
        cap[2 * n][i] = true;
        cap[i + n][2 * n + 1] = true;
        edges.push_back({2 * n, i});
        edges.push_back({i, 2 * n});
        edges.push_back({i + n, 2 * n + 1});
        edges.push_back({2 * n + 1, i + n});
    }

    for (int i = 0; i < n; i++) {
        fill(best, best + N, 1e9);
        best[2 * n] = 0;

        for (int j = 0; j < 2 * n + 1; j++) {
            for (simps& e : edges) {
                if (not cap[e.first][e.second]) continue;
                if (best[e.first] + w[e.first][e.second] < best[e.second]) {
                    best[e.second] = best[e.first] + w[e.first][e.second];
                    prv[e.second] = e.first;
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
