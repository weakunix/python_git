#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm> 

using namespace std;

int GetCell(const vector<vector<int> >& Maze, const int N, const int M, const int x, const int y) {
    if ((x < 0 or x >= M) or (y < 0 or y >= N)) return 0;
    return Maze[y][x];
}

int Bfs(const vector<vector<int> >& Maze, const int N, const int M) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    vector<int> Dist(1e7, -1);
    queue<int> NodeQueue;
    Dist[0] = 0;
    NodeQueue.push(0);
    while (not NodeQueue.empty()) {
        int CurNode = NodeQueue.front(), CurX = CurNode / 10000, CurY = (CurNode / 10) % 1000, CurSlide = (CurNode % 10) / 2 - 1, CurOrange = CurNode % 2, CurDist = Dist[CurNode];
        NodeQueue.pop();
        if (CurX == M - 1 and CurY == N - 1) return CurDist;
        if (CurSlide == -1) {
            for (int i = 0; i < 4; i++) {
                int NewX = CurX + DirX[i], NewY = CurY + DirY[i], NewCell = GetCell(Maze, N, M, NewX, NewY), NewNode;
                if (NewCell == 0 or (NewCell == 3 and CurOrange == 0)) continue;
                NewNode = NewX * 10000 + NewY * 10 + CurOrange;
                if (NewCell == 2 and CurOrange == 0) NewNode++;
                if (NewCell == 4) {
                    NewNode += 2 * (i + 1);
                    if (CurOrange == 1) NewNode--;
                }
                if (Dist[NewNode] == -1) {
                    Dist[NewNode] = CurDist + 1;
                    NodeQueue.push(NewNode);
                }
            }
        }
        else {
            int NewX = CurX + DirX[CurSlide], NewY = CurY + DirY[CurSlide], NewCell = GetCell(Maze, N, M, NewX, NewY), NewNode;
            NewNode = NewX * 10000 + NewY * 10 + CurOrange;
            if (NewCell == 0 or (NewCell == 3 and CurOrange == 0)) {
                NewNode = CurX * 10000 + CurY * 10 + CurOrange;
                CurDist--;
            }
            else if (NewCell == 2 and CurOrange == 0) NewNode++;
            else if (NewCell == 4) {
                NewNode += 2 * (CurSlide + 1);
                if (CurOrange == 1) NewNode--;
            }
            if (Dist[NewNode] == -1) {
                Dist[NewNode] = CurDist + 1;
                NodeQueue.push(NewNode);
            }
        }
    }
    return -1;
}

int main() {
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    const vector<int> MazeRow(M);
    vector<vector<int> > Maze(N, MazeRow);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) cin >> Maze[y][x];
    }
    cout << Bfs(Maze, N, M) << "\n";
    return 0;
}
