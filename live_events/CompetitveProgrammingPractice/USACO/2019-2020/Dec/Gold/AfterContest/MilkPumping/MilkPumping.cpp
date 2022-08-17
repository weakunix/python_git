#include <iostream>
#include <cstdio>
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

int N, M, Ans = 0;
vector<vector<threesome> > Graph;

int ShortestPath(const int TarFlow) {
    vector<int> Dist(N, 1e9);
    vector<bool> Visited(N);
    priority_queue<simps> NodePq;
    Dist[0] = 0;
    NodePq.push({0, 0});
    while (not NodePq.empty()) {
        int Node = NodePq.top().second;
        NodePq.pop();
        if (Visited[Node]) continue;
        Visited[Node] = true;
        for (const threesome& t : Graph[Node]) {
            int to = t.first, c = t.sec, f = t.third;
            if (f >= TarFlow and Dist[Node] + c < Dist[to]) {
                assert(not Visited[to]);
                Dist[to] = Dist[Node] + c;
                NodePq.push({-Dist[to], to});
            }
        }
    }
    if (Dist[N - 1] == 1e9) return -1;
    return (ll) 1e6 * TarFlow / Dist[N - 1];
}

int main() {
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    cin >> N >> M;
    Graph.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b, c, f;
        cin >> a >> b >> c >> f;
        a--;
        b--;
        Graph[a].push_back({b, {c, f}});
        Graph[b].push_back({a, {c, f}});
    }

    for (int i = 1; i <= 1000; i++) {
        int Cur = ShortestPath(i);
        if (Cur == -1) break;
        Ans = max(Cur, Ans);
    }

    cout << Ans << "\n";

    return 0;
}
