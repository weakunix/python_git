#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piipi;

int Bfs(const vector<vector<bool> >& Pasture, const int W, const int H, const int StartX, const int StartY, const int EndX, const int EndY) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    vector<vector<bool> > Visited;
    for (int i = 0; i < H; i++) {
        vector<bool> Row(W);
        Visited.push_back(Row);
    }
    queue<piipi> NodeQueue;
    NodeQueue.push({{StartX, StartY}, 0});
    Visited[StartY][StartX] = true;
    while (not NodeQueue.empty()) {
        int CurX = NodeQueue.front().first.first, CurY = NodeQueue.front().first.second, CurCount = NodeQueue.front().second;
        NodeQueue.pop();
        if (CurX == EndX and CurY == EndY) return CurCount - 1;
        for (int i = 0; i < 4; i++) {
            int NewX = CurX, NewY = CurY;
            while (true) {
                NewX += DirX[i];
                NewY += DirY[i];
                if ((NewX < 0 or NewX >= W) or (NewY < 0 or NewY >= H)) break;
                if (not Pasture[NewY][NewX]) break;
                if (not Visited[NewY][NewX]) {
                    Visited[NewY][NewX] = true;
                    if (CurX == 6 and CurY == 0)
                        cout << "";
                    NodeQueue.push({{NewX, NewY}, CurCount + 1});
                }
            }
        }
    }
    return -1;
}

int main() {
    int W, H, StartX = -1, StartY, EndX, EndY;
    cin >> W >> H;
    vector<vector<bool> > Pasture(H);
    for (int y = 0; y < H; y++) {
        string Row;
        cin >> Row;
        for (int x = 0; x < W; x++) {
            if (Row[x] == 'C') {
                if (StartX == -1) {
                    StartX = x;
                    StartY = y;
                }
                else {
                    EndX = x;
                    EndY = y;
                }
                Pasture[y].push_back(true);
            }
            else if (Row[x] == '.') Pasture[y].push_back(true);
            else Pasture[y].push_back(false);
        }
    }
    cout << Bfs(Pasture, W, H, StartX, StartY, EndX, EndY) << "\n";
    return 0;
}
