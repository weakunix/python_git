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

int N, M, T;
ll Ans = 0;
vector<ll> CowLocs, NodeCount, DistToN, Parent;
vector<vector<simps> > Graph;

void ShortestPath() {
    vector<bool> Visited(N);
    priority_queue<simps> NodePq;
    NodePq.push({0, 0});
    while (not NodePq.empty()) {
        ll Node = NodePq.top().second;
        NodePq.pop();
        if (Visited[Node]) continue;
        Visited[Node] = true;
        for (const simps& s : Graph[Node]) {
            int to = s.first;
            ll t = s.second;
            if (DistToN[Node] + t < DistToN[to]) {
                assert(not Visited[to]);
                DistToN[to] = DistToN[Node] + t;
                Parent[to] = Node;
                NodePq.push({-DistToN[to], to});
            }
            else if (DistToN[Node] + t == DistToN[to]) Parent[to] = min(Node, Parent[to]);
        }
    }
    return;
}

int main() {
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);

    cin >> N >> M >> T;
    CowLocs.resize(N);
    NodeCount.resize(N);
    DistToN.resize(N, 2e9);
    DistToN[0] = 0;
    Parent.resize(N, -1);
    Graph.resize(N);
    for (int i = 0; i < N; i++) cin >> CowLocs[i];
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        a--;
        b--;
        Graph[a].push_back({b, t});
        Graph[b].push_back({a, t});
    }

    ShortestPath();
    
    for (int i = 0; i < N; i++) {
        int Cur = i;
        while (Cur != -1) {
            NodeCount[Cur] += CowLocs[i];
            Cur = Parent[Cur];
        }
    }

    for (int i = 0; i < N; i++) Ans = max(NodeCount[i] * (DistToN[i] - T), Ans);

    cout << Ans << "\n";

    return 0;
}
