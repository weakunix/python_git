#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define all(v) v.begin(), v.end()

void Bfs(const vector<vector<int> >& Rooms, vector<vector<int> >& RoomOrder, const int N, const int M) {
    int CurDist = 0;
    vector<bool> Visited(N);
    queue<pii> NodeQueue;
    NodeQueue.push({M, 0});
    Visited[M] = true;
    while (NodeQueue.size() > 0) {
        int Cur = NodeQueue.front().first, Dist = NodeQueue.front().second;
        if (Dist != CurDist) {
            CurDist = Dist;
            RoomOrder.push_back({});
        }
        RoomOrder.back().push_back(Cur + 1);
        NodeQueue.pop();
        for (int i : Rooms[Cur]) {
            if (not Visited[i]) {
                Visited[i] = true;
                NodeQueue.push({i, Dist + 1});
            }
        }
    }
    return;
}

int main() {
    int N, M;
    vector<vector<int> > RoomOrder = {{}};
    cin >> N >> M;
    M--;
    vector<vector<int> > Rooms(N);
    for (int a = 0; a < N; a++) {
        for (int b = 0; b < N; b++) {
            int CanVisit;
            cin >> CanVisit;
            if (CanVisit) Rooms[a].push_back(b);
        }
    }
    Bfs(Rooms, RoomOrder, N, M);
    for (vector<int>& v : RoomOrder) {
        sort(all(v));
        for (int i : v) cout << i << " ";
        cout << "\n";
    }
    return 0;
}
