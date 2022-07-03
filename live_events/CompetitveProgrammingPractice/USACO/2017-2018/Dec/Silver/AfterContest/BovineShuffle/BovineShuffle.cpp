#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

ofstream fout("shuffle.out");
ifstream fin("shuffle.in");

int FindCycle(const vector<int>& Graph, vector<bool>& Visited, int Node) {
    int CycleStart, Count = 1;
    unordered_set<int> NodesVisited;
    while (NodesVisited.count(Node) == 0) {
        if (Visited[Node]) {
            for (int i : NodesVisited) Visited[i] = true;
            return 0;
        }
        NodesVisited.insert(Node);
        Node = Graph[Node];
    }
    CycleStart = Node;
    Node = Graph[Node];
    while (Node != CycleStart) {
        Count++;
        Node = Graph[Node];
    }
    for (int i : NodesVisited) Visited[i] = true;
    return Count;
}

int main() {
    int N, Ans = 0;
    vector<int> Graph;
    fin >> N;
    vector<bool> Visited(N);
    for (int i = 0; i < N; i++) {
        int NewLoc;
        fin >> NewLoc;
        Graph.push_back(NewLoc - 1);
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) Ans += FindCycle(Graph, Visited, i);
    }
    fout << Ans << "\n";
    return 0;
}
