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

int N;
vector<int> Id;
vector<bool> Visited;
vector<vector<simps> > Graph;

ll FindMst() {
    int Count = 0;
    ll Ans = 0;
    priority_queue<simps> NodePq;

    NodePq.push({0, 0});
    while (Count < N) {
        assert(NodePq.size() > 0);
        
        int Weight = NodePq.top().first, Node = NodePq.top().second;
        NodePq.pop();
        if (Visited[Node]) continue;
        Visited[Node] = true;
        Count++;
        Ans += Weight;
        for (const simps& s : Graph[Node]) {
            int to = s.first, w = s.second;
            NodePq.push({w, to});
        }
    }
    
    return Ans;
}

int main() {
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);

    cin >> N;
    Id.resize(N);
    Visited.resize(N);
    Graph.resize(N);
    for (int i = 0; i < N; i++) cin >> Id[i];
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            int Score = Id[i] ^ Id[j];
            Graph[i].push_back({j, Score});
        }
    }

    cout << FindMst() << "\n";

    return 0;
}
