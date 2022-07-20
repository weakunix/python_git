#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

int FloodFill(vector<vector<bool> >& Farm, const int StartingX, const int StartingY) {
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1}, Res = 0;
    queue<pii> PtQueue;
    Farm[StartingY][StartingX] = true;
    PtQueue.push({StartingX, StartingY});
    for (int i = 0; i < 4; i++) {
        int x = StartingX + DirX[i], y = StartingY + DirY[i];
        PtQueue.push({x, y});
    }
    while (not PtQueue.empty()) {
        int CurX = PtQueue.front().first, CurY = PtQueue.front().second, MissingX = 1e9, MissingY = 1e9;
        PtQueue.pop();
        if (Farm[CurY][CurX]) {
            for (int i = 0; i < 4; i++) {
                int x = CurX + DirX[i], y = CurY + DirY[i];
                if (not Farm[y][x]) {
                    if (MissingX != 1e9) {
                        MissingX = 1e9;
                        break;
                    }
                    MissingX = x;
                    MissingY = y;
                }
            }
            if (MissingX != 1e9) {
                Res++;
                Farm[MissingY][MissingX] = true;
                PtQueue.push({MissingX, MissingY});
                for (int i = 0; i < 4; i++) {
                    int x = MissingX + DirX[i], y = MissingY + DirY[i];
                    PtQueue.push({x, y});
                }
            }
        }
    }
    return Res;
}

int main() {
    //freopen("test.txt", "r", stdin);
    int N, Ans = 0;
    vector<bool> FarmRow(3000);
    vector<vector<bool> > Farm(3000, FarmRow);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        x += 1000;
        y += 1000;
        if (Farm[y][x]) Ans--;
        else Ans += FloodFill(Farm, x, y);
        cout << Ans << "\n";
    }
    return 0;
}
