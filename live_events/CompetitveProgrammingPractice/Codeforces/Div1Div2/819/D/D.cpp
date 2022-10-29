#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> pi;

void Subcase() {
    int N, M;
    cin >> N >> M;
    vector<int> First;
    vector<bool> Visited(N), Ans(M);
    vector<vector<pi> > Graph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Graph[a].push_back({b, i});
        Graph[b].push_back({a, i});
        
        if (Graph[a].size() > 1) First.push_back(a);
        if (Graph[b].size() > 1) First.push_back(b);
    }

    queue<pi> NodeQ;

    for (int i : First) {
        for (pi p : Graph[i]) NodeQ.push(p);
    }

    while (not NodeQ.empty()) {
        int Node = NodeQ.front().first, Edge = NodeQ.front().second;

        NodeQ.pop();

        if (Visited[Node]) continue;

        Visited[Node] = true;
        Ans[Edge] = true;

        for (pi p : Graph[Node]) NodeQ.push(p);
    }
    
    for (bool b : Ans) cout << b;
    cout << "\n";

    return;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) Subcase();

    return 0;
}
