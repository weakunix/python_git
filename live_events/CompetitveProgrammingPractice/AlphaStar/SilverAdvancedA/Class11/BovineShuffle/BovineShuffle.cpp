#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

int FindCycle(const vector<int>& Shuffle, vector<bool>& Visited, int CurNode) {
    int CycleStart, CycleCount = 0;
    unordered_set<int> ThisIteration;
    while (not Visited[CurNode]) {
        Visited[CurNode] = true;
        ThisIteration.insert(CurNode);
        CurNode = Shuffle[CurNode];
    }
    if (ThisIteration.count(CurNode) > 0) {
        CycleStart = CurNode;
        CycleCount++;
        CurNode = Shuffle[CurNode];
        while (CurNode != CycleStart) {
            CycleCount++;
            CurNode = Shuffle[CurNode];
        }
    }
    return CycleCount;
}

int main() {
    int N, Ans = 0;
    cin >> N;
    vector<int> Shuffle(N);
    vector<bool> Visited(N);
    for (int i = 0; i < N; i++) {
        int Dest;
        cin >> Dest;
        Dest--;
        Shuffle[i] = Dest;
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) Ans += FindCycle(Shuffle, Visited, i);
    }
    cout << Ans << "\n";
    return 0;
}
