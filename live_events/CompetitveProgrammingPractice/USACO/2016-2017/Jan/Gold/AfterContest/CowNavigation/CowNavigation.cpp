#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct Node {
    int x1, y1, dir1, x2, y2, dir2;
};

bool operator<(const Node& a, const Node& b) {
    if (a.x1 != b.x1) return a.x1 < b.x1;
    if (a.y1 != b.y1) return a.y1 < b.y1;
    if (a.dir1 != b.dir1) return a.dir1 < b.dir1;
    if (a.x2 != b.x2) return a.x2 < b.x2;
    if (a.y2 != b.y2) return a.y2 < b.y2;
    return a.dir2 < b.dir2;
}

bool ShouldMove(const vector<vector<bool> >& Barn, const int N, int x, int y, const int dirx, const int diry) {
    if (x == N - 1 and y == 0) return false;
    x += dirx;
    y += diry;
    return (((x >= 0 and x < N) and (y >= 0 and y < N)) and Barn[y][x]);
}

int Bfs(const vector<vector<bool> >& Barn, const int N) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, -1, 0, 1};
    queue<Node> NodeQueue;
    map<Node, int> Dist = {{{0, N - 1, 0, 0, N - 1, 1}, 0}};
    NodeQueue.push({0, N - 1, 0, 0, N - 1, 1});
    while (not NodeQueue.empty()) {
        Node CurNode = NodeQueue.front(), NewNode = CurNode;
        int CurDist = Dist[CurNode];
        NodeQueue.pop();
        if ((CurNode.x1 == N - 1 and CurNode.y1 == 0) and (CurNode.x2 == N - 1 and CurNode.y2 == 0)) return CurDist;
        NewNode.dir1 = (NewNode.dir1 + 1) % 4;
        NewNode.dir2 = (NewNode.dir2 + 1) % 4;
        if (Dist.count(NewNode) == 0) {
            Dist[NewNode] = CurDist + 1;
            NodeQueue.push(NewNode);
        }
        NewNode.dir1 = (NewNode.dir1 + 2) % 4;
        NewNode.dir2 = (NewNode.dir2 + 2) % 4;
        if (Dist.count(NewNode) == 0) {
            Dist[NewNode] = CurDist + 1;
            NodeQueue.push(NewNode);
        }
        NewNode.dir1 = (NewNode.dir1 + 1) % 4;
        NewNode.dir2 = (NewNode.dir2 + 1) % 4;
        if (ShouldMove(Barn, N, NewNode.x1, NewNode.y1, DirX[NewNode.dir1], DirY[NewNode.dir1])) {
            NewNode.x1 += DirX[NewNode.dir1];
            NewNode.y1 += DirY[NewNode.dir1];
        }
        if (ShouldMove(Barn, N, NewNode.x2, NewNode.y2, DirX[NewNode.dir2], DirY[NewNode.dir2])) {
            NewNode.x2 += DirX[NewNode.dir2];
            NewNode.y2 += DirY[NewNode.dir2];
        }
        if (Dist.count(NewNode) == 0) {
            Dist[NewNode] = CurDist + 1;
            NodeQueue.push(NewNode);
        }
    }
    return -1;
}

int main() {
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);
    int N;
    cin >> N;
    const vector<bool> BarnRow(N);
    vector<vector<bool> > Barn(N, BarnRow);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            char Cell;
            cin >> Cell;
            Barn[y][x] = (Cell == 'E');
        }
    }
    cout << Bfs(Barn, N) << "\n";
    return 0;
}
