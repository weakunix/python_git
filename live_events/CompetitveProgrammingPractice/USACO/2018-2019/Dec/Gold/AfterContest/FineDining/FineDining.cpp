#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> simps;

int N, M, K;
vector<ll> ShortestDistToN, DistWithEat;
vector<simps> Haybales;
vector<vector<simps> > Graph;

void ShortestPath(vector<ll>& DistVector) {
    vector<bool> Visited(N);
    priority_queue<simps> NodePq;
    DistVector[N - 1] = 0;
    NodePq.push({0, N - 1});
    while (not NodePq.empty()) {
        ll Node = NodePq.top().second;
        NodePq.pop();
        if (Visited[Node]) continue;
        Visited[Node] = true;
        for (const simps& s : Graph[Node]) {
            ll to = s.first, t = s.second;
            if (to == N - 1) continue;
            if (DistVector[Node] + t < DistVector[to]) {
                assert(not Visited[to]);
                DistVector[to] = DistVector[Node] + t;
                NodePq.push({-DistVector[to], to});
            }
        }
    }
    return;
}

int main() {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);

    ll ClosestHaybale = 2e10;
    cin >> N >> M >> K;
    ShortestDistToN.resize(N, 2e10);
    DistWithEat.resize(N, 2e10);
    Graph.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--;
        b--;
        Graph[a].push_back({b, t});
        Graph[b].push_back({a, t});
    }

    ShortestPath(ShortestDistToN);
    
    Graph[N - 1].clear();
    for (int i = 0; i < K; i++) {
        int idx, y;
        cin >> idx >> y;
        idx--;
        Graph[N - 1].push_back({idx, ShortestDistToN[idx] - y});
        ClosestHaybale = min(2 * ShortestDistToN[idx] - y, ClosestHaybale);
    }
    ShortestPath(DistWithEat);

    for (int i = 0; i < N - 1; i++) {
        DistWithEat[i] = min(ShortestDistToN[i] + ClosestHaybale, DistWithEat[i]);
        cout << ((int) DistWithEat[i] <= ShortestDistToN[i]) << "\n";
    }

    return 0;
}
