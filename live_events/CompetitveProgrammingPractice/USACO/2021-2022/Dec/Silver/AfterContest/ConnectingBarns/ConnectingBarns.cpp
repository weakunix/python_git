#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void Dfs(const vector<vector<int> >& Connections, vector<bool>& Visited, vector<int>& NodeToComp, const int Comp, const int Barn) {
    Visited[Barn] = true;
    NodeToComp[Barn] = Comp;
    for (int i : Connections[Barn]) {
        if (not Visited[i]) Dfs(Connections, Visited, NodeToComp, Comp, i);
    }
    return;
}

ll MinCost(const int a, const int b, const vector<vector<int> >& ConComps) {
    int Dist = 1e5;
    for (int i : ConComps[a]) {
        int ClosestBarn = lower_bound(ConComps[b].begin(), ConComps[b].end(), i) - ConComps[b].begin();
        if (ClosestBarn > 0) Dist = min(abs(ConComps[b][ClosestBarn - 1] - i), Dist);
        if (ClosestBarn < ConComps[b].size()) Dist = min(abs(ConComps[b][ClosestBarn] - i), Dist);
    }
    return (ll)Dist * Dist;
}

void Subcase() {
    int N, M, NumOfComp = 0;
    cin >> N >> M;
    vector<int> NodeToComp(N);
    vector<bool> Visited(N);
    vector<vector<int> > Connections(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Connections[a].push_back(b);
        Connections[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) {
            Dfs(Connections, Visited, NodeToComp, NumOfComp, i);
            NumOfComp++;
        }
    }
    vector<vector<int> > ConComps(NumOfComp);
    for (int i = 0; i < N; i++) ConComps[NodeToComp[i]].push_back(i);
    ll Ans = MinCost(NodeToComp[0], NodeToComp[N - 1], ConComps);
    for (int i = 1; i < NumOfComp; i++) Ans = min(MinCost(i, NodeToComp[0], ConComps) + MinCost(i, NodeToComp[N - 1], ConComps), Ans);
    cout << Ans << "\n";
    return;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) Subcase();
}
