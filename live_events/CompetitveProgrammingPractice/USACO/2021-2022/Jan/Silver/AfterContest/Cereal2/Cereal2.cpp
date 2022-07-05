#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Edge {
    int CowNum;
    int StartingNode;
    int NextNode;
    bool IsFirstChoice;
};

void Dfs(const vector<vector<Edge> >& Graph, vector<bool>& Visited, vector<int>& ConCompNodes, set<int>& ConCompEdges, const int Node, Edge& ExtraEdge) {
    Visited[Node] = true;
    ConCompNodes.push_back(Node);
    for (const Edge& e: Graph[Node]) {
        if (ConCompEdges.count(e.CowNum) == 0) {
            ConCompEdges.insert(e.CowNum);
            if (Visited[e.NextNode]) ExtraEdge = e;
            else Dfs(Graph, Visited, ConCompNodes, ConCompEdges, e.NextNode, ExtraEdge);
        }
    }
    return;
}

void EdgeOrderingDfs(const vector<vector<Edge> >& Graph, vector<bool>& Visited, set<int>& ConCompEdges, vector<int>& PickFirst, vector<int>& PickSecond, vector<int>& PickLast, const int Node) {
    Visited[Node] = true;
    for (const Edge& e : Graph[Node]) {
        if (ConCompEdges.count(e.CowNum) == 0) {
            ConCompEdges.insert(e.CowNum);
            if (not Visited[e.NextNode]) {
                if (e.IsFirstChoice) PickFirst.push_back(e.CowNum);
                else PickSecond.push_back(e.CowNum);
                EdgeOrderingDfs(Graph, Visited, ConCompEdges, PickFirst, PickSecond, PickLast, e.NextNode);
            }
            else PickLast.push_back(e.CowNum);
        }
    }
}

void SolveConComp(const vector<vector<Edge> >& Graph, vector<bool>& Visited, const int M, int StartingNode, int& Ans, vector<int>& PickFirst, vector<int>& PickSecond, vector<int>& PickLast) {
    Edge ExtraEdge = {-1, -1, -1, false};
    vector<int> ConCompNodes;
    vector<bool> SecondVisited(M);
    set<int> ConCompEdges;
    Dfs(Graph, Visited, ConCompNodes, ConCompEdges, StartingNode, ExtraEdge);
    Ans += ConCompNodes.size();
    ConCompEdges.clear();
    if (ExtraEdge.CowNum == -1) Ans--;
    else {
        if (ExtraEdge.IsFirstChoice) StartingNode = ExtraEdge.NextNode;
        else StartingNode = ExtraEdge.StartingNode;
        PickFirst.push_back(ExtraEdge.CowNum);
        ConCompEdges.insert(ExtraEdge.CowNum);
    }
    EdgeOrderingDfs(Graph, SecondVisited, ConCompEdges, PickFirst, PickSecond, PickLast, StartingNode);
    return;
}

int main() {
    int N, M, Ans = 0;
    vector<int> PickFirst, PickSecond, PickLast;
    cin >> N >> M;
    vector<vector<Edge> > Graph(M);
    vector<bool> Visited(M);
    for (int i = 1; i <= N; i++) {
        int First, Second;
        cin >> First >> Second;
        First--;
        Second--;
        Graph[First].push_back({i, First, Second, false});
        Graph[Second].push_back({i, Second, First, true});
    }
    for (int i = 0; i < M; i++) {
        if (not Visited[i]) SolveConComp(Graph, Visited, M, i, Ans, PickFirst, PickSecond, PickLast);
    }
    cout << N - Ans << "\n";
    for (int i : PickFirst) cout << i << "\n";
    for (int i : PickSecond) cout << i << "\n";
    for (int i : PickLast) cout << i << "\n";
    return 0;
}
