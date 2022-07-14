#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void Bfs(const vector<vector<int> >& Graph, vector<int>& Dists, const int StartingNode) {
    queue<int> NodeQueue, DistQueue;
    Dists[StartingNode] = 0;
    NodeQueue.push(StartingNode);
    while (not NodeQueue.empty()) {
        int CurNode = NodeQueue.front();
        NodeQueue.pop();
        for (int i : Graph[CurNode]) {
            if (Dists[i] == -1) {
                Dists[i] = Dists[CurNode] + 1;
                NodeQueue.push(i);
            }
        }
    }
    return;
}

int main() {
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);
    int B, E, P, N, M, Ans = 2e9;
    cin >> B >> E >> P >> N >> M;
    vector<int> Bessie(N, -1), Elsie(N, -1), Barn(N, -1);
    vector<vector<int> > Graph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }
    Bfs(Graph, Bessie, 0);
    Bfs(Graph, Elsie, 1);
    Bfs(Graph, Barn, N - 1);
    for (int i = 0; i < N; i++) Ans = min(Bessie[i] * B + Elsie[i] * E + Barn[i] * P, Ans);
    cout << Ans << "\n";
    return 0;
}
