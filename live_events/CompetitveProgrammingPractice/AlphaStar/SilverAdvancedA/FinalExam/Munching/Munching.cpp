#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

int Bfs(vector<vector<bool> >& Visited, const int R, const int C, const int Sx, const int Sy, const int Ex, const int Ey) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    queue<piipi> CellQueue;
    CellQueue.push({{Sx, Sy}, 0});
    Visited[Sy][Sx] = true;
    while (not CellQueue.empty()) {
        int CurX = CellQueue.front().first.first, CurY = CellQueue.front().first.second, CurDist = CellQueue.front().second;
        CellQueue.pop();
        if (CurX == Ex and CurY == Ey) return CurDist;
        for (int i = 0; i < 4; i++) {
            int x = CurX + DirX[i], y = CurY + DirY[i];
            if ((x >= 0 and x < C) and (y >= 0 and y < R)) {
                if (not Visited[y][x]) {
                    Visited[y][x] = true;
                    CellQueue.push({{x, y}, CurDist + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    int R, C, Sx, Sy, Ex, Ey;
    cin >> R >> C;
    vector<vector<bool> > Visited;
    for (int y = 0; y < R; y++) {
        Visited.push_back({});
        for (int x = 0; x < C; x++) {
            char Cell;
            cin >> Cell;
            Visited[y].push_back((Cell == '*'));
            if (Cell == 'C') {
                Sx = x;
                Sy = y;
            }
            else if (Cell == 'B') {
                Ex = x;
                Ey = y;
            }
        }
    }
    cout << Bfs(Visited, R, C, Sx, Sy, Ex, Ey) << "\n";
    return 0;
}
