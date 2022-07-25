#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

const int ModVal = 1e9 + 7;
int N, M, X, Y, CompCount = 0;
ll Ans = 0;
vector<int> CompsOfNodes;
vector<vector<int> > CompDists, Dp;
vector<vector<simps> > Graph;

void DfsFindComps(const int CurComp, const int Node) {
    CompsOfNodes[Node] = CurComp;
    for (const simps& s : Graph[Node]) {
        if (CompsOfNodes[s.first] == -1) DfsFindComps(CurComp, s.first);
    }
    return;
}

int BfsNodeDist(const int StartNode, const int EndNode) {
    queue<simps> NodeQueue;
    vector<int> Visited(N);
    NodeQueue.push({StartNode, 0});
    Visited[StartNode] = true;
    while (not NodeQueue.empty()) {
        int CurNode = NodeQueue.front().first, CurDist = NodeQueue.front().second;
        NodeQueue.pop();
        if (CurNode == EndNode) return CurDist;
        for (const simps& s : Graph[CurNode]) {
            if (not Visited[s.first]) {
                NodeQueue.push({s.first, CurDist + s.second});
                Visited[s.first] = true;
            }
        }
    }
    return -1;
}

int main() {
    freopen("mooriokart.in", "r", stdin);
    //freopen("mooriokart.out", "w", stdout);
    cin >> N >> M >> X >> Y;
    CompsOfNodes.resize(N, -1);
    Graph.resize(N);
    for (int i = 0; i < M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a--;
        b--;
        Graph[a].push_back({b, d});
        Graph[b].push_back({a, d});
    }
    for (int i = 0; i < N; i++) {
        if (CompsOfNodes[i] == -1) {
            DfsFindComps(CompCount, i);
            CompCount++;
        }
    }
    CompDists.resize(CompCount);
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (CompsOfNodes[i] == CompsOfNodes[j]) CompDists[CompsOfNodes[i]].push_back(BfsNodeDist(i, j));
        }
    }
    for (int i = 0; i <= Y; i++) {
        vector<int> DpRow(CompCount);
        Dp.push_back(DpRow);
    }
    for (int i : CompDists[0]) {
        if (i >= Y) Ans = (Ans + i) % ModVal;
        Dp[min(i, Y)][0]++;
    }
    for (int i = 0; i < CompCount; i++) {
        for (int j : CompDists[i + 1] {
            for (int k = 0; k <= Y; k++) {
                //TODO
            }
        }
    }
    return 0;
}
