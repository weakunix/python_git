#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

int Bfs(const vector<vector<bool> >& Lake, const int M, const int N, const int A, const int B, const pii& Start, const pii& End) {
    vector<int> First = {A, A, B, B, -A, -A, -B, -B}, Second = {B, -B, A, -A, B, -B, A, -A};
    vector<vector<bool> > Visited;
    for (int y = 0; y < M; y++) {
        vector<bool> Row(N);
        Visited.push_back(Row);
    }
    queue<piipi> NodeQueue;
    NodeQueue.push({Start, 0});
    Visited[Start.second][Start.first] = true;
    while (not NodeQueue.empty()) {
        int Jumps = NodeQueue.front().second;
        pii Point = NodeQueue.front().first;
        if (Point == End) return Jumps;
        NodeQueue.pop();
        for (int i = 0; i < 8; i++) {
            int NewX = Point.first + First[i], NewY = Point.second + Second[i];
            if ((NewX >= 0 and NewX < N) and (NewY >= 0 and NewY < M)) {
                if (not Visited[NewY][NewX] and Lake[NewY][NewX]) {
                    Visited[NewY][NewX] = true;
                    NodeQueue.push({{NewX, NewY}, Jumps + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    int M, N, A, B;
    pii Start, End;
    vector<vector<bool> > Lake;
    cin >> M >> N >> A >> B;
    for (int y = 0; y < M; y++) {
        vector<bool> Row(N);
        Lake.push_back(Row);
        for (int x = 0; x < N; x++) {
            int Type;
            cin >> Type;
            if (Type == 0 or Type == 2) Lake[y][x] = false;
            else {
                Lake[y][x] = true;
                if (Type == 3) Start = {x, y};
                else if (Type == 4) End = {x, y};
            }
        }
    }
    cout << Bfs(Lake, M, N, A, B, Start, End) << "\n";
    return 0;
}
