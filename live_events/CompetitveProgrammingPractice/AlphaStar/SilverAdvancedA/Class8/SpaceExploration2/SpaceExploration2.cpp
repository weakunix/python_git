#include <iostream>
#include <queue>

using namespace std;

void solve() {
    int N, Ans = 0;
    cin >> N;
    bool Visited[2001][2001];
    int DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    for (int y = 0; y < N; y++) {
        string Row;
        cin >> Row;
        for (int x = 0; x < N; x++) if (Row[x] == '.') Visited[y][x] = true;
    }
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (not Visited[y][x]) {
                Ans++;
                //Bfs
                queue<int> XVals, YVals;
                XVals.push(x);
                YVals.push(y);
                Visited[y][x] = true;
                while (not XVals.empty()) {
                    int CurX = XVals.front(), CurY = YVals.front();
                    XVals.pop();
                    YVals.pop();
                    for (int i = 0; i < 4; i++) {
                        int NewX = CurX + DirX[i], NewY = CurY + DirY[i];
                        if ((NewX >= 0 and NewX < N) and (NewY >= 0 and NewY < N)) {
                            if (not Visited[NewY][NewX]) {
                                Visited[NewY][NewX] = true;
                                XVals.push(NewX);
                                YVals.push(NewY);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << Ans << "\n";
    return;
}

int main() {
    solve();
    return 0;
}
