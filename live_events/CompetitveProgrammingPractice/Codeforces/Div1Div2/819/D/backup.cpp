#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> pi;

void Dfs(const vector<vector<pi> >& Graph, vector<bool>& Visited, vector<bool>& Ans, const int Node, const int Edge) {
    Visited[Node] = true;
    if (Edge != -1) Ans[Edge] = true;
    
    for (const pi& p : Graph[Node]) {
        if (Visited[p.first]) continue;
        Dfs(Graph, Visited, Ans, p.first, p.second);
    }

    return;
}

void Subcase() {
    int N, M;
    cin >> N >> M;
    vector<bool> Visited(N), Ans(M);
    vector<vector<pi> > Graph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Graph[a].push_back({b, i});
        Graph[b].push_back({a, i});
    }
    
    Dfs(Graph, Visited, Ans, 0, -1);

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
