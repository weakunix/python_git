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

int n, m, q;
vector<vector<ll>> dist;

int main() {
    cin >> n >> m >> q;
    dist.resize(n, vector<ll>(n, 1e12));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        dist[a][b] = min(c, dist[a][b]);
        dist[b][a] = min(c, dist[b][a]);
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (dist[a][b] == 1e12 ? -1 : dist[a][b]) << "\n";
    }
	return 0;
}
