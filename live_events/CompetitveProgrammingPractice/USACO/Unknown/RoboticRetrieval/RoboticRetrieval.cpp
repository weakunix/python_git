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

const int N = 200, M = 200, K = N * N;

int n, m, arr[M][N], dist[K], cnt = 1;
simps to[K];
vector<int> ans;
vector<simps> adj[K];

int main() {
    memset(dist, -1, sizeof(dist));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            arr[i][j]--;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                int a = arr[k][i], b = arr[k][j];
                adj[n * a + b].push_back({n * i + j, k});
            }
        }
    }

    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (not q.empty()) {
        int cur = q.front();
        q.pop();
        for (simps s : adj[cur]) {
            if (dist[s.first] == -1) {
                dist[s.first] = dist[cur] + 1;
                to[s.first] = {cur, s.second};
                q.push(s.first);
                cnt++;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        int cur = i;
        for (int j : ans) cur = arr[j][cur];
        while (cur != 0) {
            ans.push_back(to[cur].second);
            cur = to[cur].first;
        }
    }

    assert(cnt == n * n);
    return 0; //TODO

    for (int i : ans) cout << i + 1 << "\n";

    /*
    for (int i = 0; i < n; i++) {
        int cur = i;
        cout << cur << ": ";
        for (int j : ans) {
            cur = arr[j][cur];
            cout << cur << " ";
        }
        cout << "\n";
    }
    */

	return 0;
}
