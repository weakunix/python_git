#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<simps, int> threesome;

int Bfs(const vector<vector<bool> >& CommsGraph, const vector<int>& Cows, const int N, const int K) {
    const vector<bool> VisitedRow(N);
    vector<vector<bool> > Visited(K, VisitedRow);
    deque<threesome> NodeDeque;
    NodeDeque.push_back({{Cows[0], 0}, 0});
    Visited[Cows[0]][0] = true;
    while (not NodeDeque.empty()) {
        int CurBreed = NodeDeque.front().first.first, CurLoc = NodeDeque.front().first.second, CurDist = NodeDeque.front().second;
        NodeDeque.pop_front();
        if (CurLoc > 0 and not Visited[CurBreed][CurLoc - 1]) {
            Visited[CurBreed][CurLoc - 1] = true;
            NodeDeque.push_back({{CurBreed, CurLoc - 1}, CurDist + 1});
        }
        if (CurLoc < N - 1 and not Visited[CurBreed][CurLoc + 1]) {
            Visited[CurBreed][CurLoc + 1] = true;
            NodeDeque.push_back({{CurBreed, CurLoc + 1}, CurDist + 1});
        }
        if (CommsGraph[CurBreed][Cows[CurLoc]]) {
            if (CurLoc == N - 1) return CurDist;
            if (not Visited[Cows[CurLoc]][CurLoc]) {
                Visited[Cows[CurLoc]][CurLoc] = true;
                NodeDeque.push_front({{Cows[CurLoc], CurLoc}, CurDist});
            }
        }
    }
    return -1;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> Cows(N);
    const vector<bool> CommsRow(K);
    vector<vector<bool> > CommsGraph(K, CommsRow);
    for (int i = 0; i < N; i++) {
        cin >> Cows[i];
        Cows[i]--;
    }
    for (int a = 0; a < K; a++) {
        for (int b = 0; b < K; b++) {
            char c;
            cin >> c;
            CommsGraph[a][b] = (c == '1');
        }
    }
    cout << Bfs(CommsGraph, Cows, N, K) << "\n";
    return 0;
}
