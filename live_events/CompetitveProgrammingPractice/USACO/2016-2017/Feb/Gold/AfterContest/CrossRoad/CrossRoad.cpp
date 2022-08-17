#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;

int N, T, DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
vector<vector<int> > Grid;
vector<vector<simps> > Graph;

void FindPaths(const int Node, const int x, const int y, const int CurStep) {
    if (CurStep < 3) {
        for (int i = 0; i < 4; i++) {
            int curx = x + DirX[i], cury = y + DirY[i];
            if ((curx < 0 or curx >= N) or (cury < 0 or cury >= N)) continue;
            FindPaths(Node, curx, cury, CurStep + 1);
        }
        return;
    }
    assert(CurStep == 3);
    Graph[Node].push_back({y * N + x, 3 * T + Grid[y][x]});
    return;
}

int main() {
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);

    cin >> N >> T;
    Grid.resize(N);
    Graph.resize(N * N);
    for (int y = 0; y < N; y++) {
        Grid[y].resize(N);
        for (int x = 0; x < N; x++) cin >> Grid[y][x];
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) FindPaths(y * N + x, x, y, 0);
    }
    
    vector<ll> Dist(N * N, -1);
    vector<bool> Visited(N * N);
    priority_queue<simps> NodePq;
    Dist[0] = 0;
    NodePq.push({0, 0});
    while (not NodePq.empty()) {
        int Node = NodePq.top().second;
        NodePq.pop();
        if (Visited[Node]) continue;
        Visited[Node] = true;
        for (const simps& s : Graph[Node]) {
            int to = s.first;
            ll d = s.second;
            if (Dist[to] == -1 or Dist[Node] + d < Dist[to]) {
                assert(not Visited[to]);
                Dist[to] = Dist[Node] + d;
                NodePq.push({-Dist[to], to});
            }
        }
    }

    int LastNode = N * N - 1;
    ll Ans = Dist[LastNode];
    vector<simps> Psbl = {{LastNode - 1, 1}, {LastNode - N, 1}, {LastNode - 2, 2}, {LastNode - 1 - N, 2}, {LastNode - 2 * N, 2}};
    for (const simps& s : Psbl) Ans = min(Dist[s.first] + s.second * T, Ans);

    cout << Ans << "\n";

    return 0;
}
