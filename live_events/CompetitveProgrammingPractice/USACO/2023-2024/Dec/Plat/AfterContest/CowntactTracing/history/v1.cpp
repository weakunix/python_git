#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 30, Q = 20; //BFI ONLY

int n, q, queries[Q], ans[Q];
bool inf[N], vis[N];
vector<int> adj[N];

int main() {
    fill(ans, ans + Q, 1e9);

    cin >> n;
    assert(n <= 30);

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        inf[i] = (c == '1');
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cin >> q;
    for (int i = 0; i < q; i++) cin >> queries[i];

    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < q; j++) {
            memset(vis, false, sizeof(vis));
            queue<simps> qu;

            for (int k = 0; k < n; k++) {
                if ((1 << k) & i) {
                    qu.push({k, queries[j]});
                    vis[k] = true;
                }
            }

            while (not qu.empty()) {
                int node = qu.front().first, dist = qu.front().second;
                qu.pop();
                if (not dist) continue;
                for (int k : adj[node]) {
                    if (not vis[k]) {
                        qu.push({k, dist - 1});
                        vis[k] = true;
                    }
                }
            }

            bool works = true;
            for (int k = 0; k < n; k++) {
                if (inf[k] != vis[k]) {
                    works = false;
                    break;
                }
            }

            if (works) ans[j] = min(__builtin_popcount(i), ans[j]);
        }
    }

    for (int i = 0; i < q; i++) cout << (ans[i] == 1e9 ? -1 : ans[i]) << "\n";

	return 0;
}
