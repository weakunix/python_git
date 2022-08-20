#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;

int N, M, C;
vector<int> Ans, Indegree, TopologicalSort;
vector<vector<simps> > Graph, InverseGraph;

void BfsTopologicalSort() {
    queue<int> NodeQueue;
    for (int i = 0; i < N; i++) {
        if (Indegree[i] == 0) NodeQueue.push(i);
    }
    while (not NodeQueue.empty()) {
        int Node = NodeQueue.front();
        NodeQueue.pop();
        TopologicalSort.push_back(Node);
        for (const simps& s : Graph[Node]) {
            int to = s.first;
            Indegree[to]--;
            if (Indegree[to] == 0) NodeQueue.push(to);
            assert(Indegree[to] >= 0);
        }
    }
    assert(TopologicalSort.size() == N);
    return;
}

int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);

    cin >> N >> M >> C;
    Ans.resize(N);
    Indegree.resize(N);
    Graph.resize(N);
    InverseGraph.resize(N);
    for (int i = 0; i < N; i++) cin >> Ans[i];
    for (int i = 0; i < C; i++) {
        int a, b, x;
        cin >> a >> b >> x;
        a--;
        b--;
        Indegree[b]++;
        Graph[a].push_back({b, x});
        InverseGraph[b].push_back({a, x});
    }

    BfsTopologicalSort();

    for (int i : TopologicalSort) {
        for (const simps& s : InverseGraph[i]) {
            int from = s.first, x = s.second;
            Ans[i] = max(Ans[from] + x, Ans[i]);
            assert(Ans[i] > 0 and Ans[i] <= M);
        }
    }

    for (int i : Ans) cout << i << "\n";

    return 0;
}
