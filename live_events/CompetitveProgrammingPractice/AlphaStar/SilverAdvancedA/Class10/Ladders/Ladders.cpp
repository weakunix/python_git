#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

void FloodFill(vector<vector<bool> >& Visited, const int StartX, const int StartY) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    queue<pii> CellQueue;
    CellQueue.push({StartX, StartY});
    Visited[StartY][StartX] = true;
    while (not CellQueue.empty()) {
        int x = CellQueue.front().first, y = CellQueue.front().second;
        CellQueue.pop();
        for (int i = 0; i < 4; i++) {
            int NewX = x + DirX[i], NewY = y + DirY[i];
            if ((NewX >= 0 and NewX <= 4000) and (NewY >= 0 and NewY <= 4000)) {
                if (not Visited[NewY][NewX]) {
                    Visited[NewY][NewX] = true;
                    CellQueue.push({NewX, NewY});
                }
            }
        }
    }
    return;
}

int main() {
    int N, CurX = 2000, CurY = 2000, Ans = 0;
    vector<vector<bool> > Visited;
    for (int i = 0; i <= 4000; i++) {
        vector<bool> Row(4001);
        Visited.push_back(Row);
    }
    Visited[2000][2000] = true;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int DirX = 0, DirY = 0;
        char c;
        cin >> c;
        if (c == 'N') DirY = 1;
        else if (c == 'E') DirX = 1;
        else if (c == 'S') DirY = -1;
        else DirX = -1;
        for (int j = 0; j < 2; j++) {
            CurX += DirX;
            CurY += DirY;
            Visited[CurY][CurX] = true;
        }
    }
    for (int y = 0; y <= 4000; y++) {
        for (int x = 0; x <= 4000; x++) {
            if (not Visited[y][x]) {
                Ans++;
                FloodFill(Visited, x, y);
            }
        }
    }
    cout << Ans - 1 << "\n";
    return 0;
}
