#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

int Dfs(const vector<vector<int> >& Graph, vector<int>& DistFromLeaf, const int CurNode, const int Parent) {
    int Dist = 1e9;
    for (int i : Graph[CurNode]) {
        if (i != Parent) Dist = min(Dfs(Graph, DistFromLeaf, i, CurNode), Dist);
    }
    if (Dist == 1e9) Dist = 0;
    else Dist++;
    DistFromLeaf[CurNode] = Dist;
    return Dist;
}

int Bfs(const vector<vector<int> >& Graph, const vector<int>& DistFromLeaf, const int StartingNode) {
    int Res = 0;
    queue<simps> NodeQueue;
    vector<int> Visited(Graph.size());
    NodeQueue.push({StartingNode, 0});
    Visited[StartingNode] = true;
    while (not NodeQueue.empty()) {
        int CurNode = NodeQueue.front().first, DistFromRoot = NodeQueue.front().second;
        NodeQueue.pop();
        if (DistFromLeaf[CurNode] <= DistFromRoot) {
            Res++;
            continue;
        }
        for (int i : Graph[CurNode]) {
            if (not Visited[i]) {
                Visited[i] = true;
                NodeQueue.push({i, DistFromRoot + 1});
            }
        }
    }
    return Res;
}

int main() {
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    int N, K;
    cin >> N >> K;
    vector<int> DistFromLeaf(N);
    vector<vector<int> > Graph(N);
    K--;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }
    Dfs(Graph, DistFromLeaf, K, -1);
    cout << Bfs(Graph, DistFromLeaf, K) << "\n";
    return 0;
}
