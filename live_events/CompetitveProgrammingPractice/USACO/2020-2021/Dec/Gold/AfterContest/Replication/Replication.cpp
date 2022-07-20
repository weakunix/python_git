#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<simps, int> threesome;

const int MaxN = 1000;
int N, DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1}, DistFromRock[MaxN][MaxN];
ll D;
bool Grid[MaxN][MaxN], PsblCenters[MaxN][MaxN], Visited[MaxN][MaxN];
vector<simps> Starts, CentersByDist[MaxN / 2 + 1];

void FFRockDist() {
    queue<simps> CellQueue;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            
            if (not Grid[y][x]) {
                DistFromRock[y][x] = 0;
                CellQueue.push({x, y});
            }
            else DistFromRock[y][x] = -1;
        }
    }
    while (not CellQueue.empty()) {
        int CurX = CellQueue.front().first, CurY = CellQueue.front().second;
        CellQueue.pop();
        for (int i = 0; i < 4; i++) {
            int NewX = CurX + DirX[i], NewY = CurY + DirY[i];
            if ((NewX >= 0 and NewX < N) and (NewY >= 0 and NewY < N)) {
                if (DistFromRock[NewY][NewX] == -1) {
                    DistFromRock[NewY][NewX] = DistFromRock[CurY][CurX] + 1;
                    CellQueue.push({NewX, NewY});
                }
            }
        }
    }
    return;
}

void FFPsblCenters() {
    queue<threesome> CellQueue;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) PsblCenters[y][x] = false;
    }
    for (simps s : Starts) {
        CellQueue.push({s, 0});
        PsblCenters[s.second][s.first] = true;
        CentersByDist[DistFromRock[s.second][s.first] - 1].push_back(s);
    }
    while (not CellQueue.empty()) {
        int x = CellQueue.front().first.first, y = CellQueue.front().first.second, t = CellQueue.front().second;
        CellQueue.pop();
        if (t < D * DistFromRock[y][x]) {
            for (int i = 0; i < 4; i++) {
                int nx = x + DirX[i], ny = y + DirY[i];
                if (not PsblCenters[ny][nx] and t + 1 <= D * DistFromRock[ny][nx]) {
                    PsblCenters[ny][nx] = true;
                    CellQueue.push({{nx, ny}, t + 1});
                    CentersByDist[DistFromRock[ny][nx] - 1].push_back({nx, ny});
                }
            }
        }
    }
    return;
}

int FFReachable() {
    int Res = 0;
    queue<simps> CellQueue;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) Visited[y][x] = false;
    }
    for (int i = N / 2; i >= 0; i--) {
        for (simps s : CentersByDist[i]) {
            if (not Visited[s.second][s.first]) {
                CellQueue.push(s);
                Visited[s.second][s.first] = true;
                Res++;
            }
        }
        if (i == 0) break;
        int Times = CellQueue.size();
        for (int j = 0; j < Times; j++) {
            int x = CellQueue.front().first, y = CellQueue.front().second;
            CellQueue.pop();
            for (int k = 0; k < 4; k++) {
                int nx = x + DirX[k], ny = y + DirY[k];
                if (not Visited[ny][nx] and Grid[ny][nx]) {
                    Visited[ny][nx] = true;
                    CellQueue.push({nx, ny});
                    Res++;
                }
            }
        }
    }
    return Res;
}

int main() {
    //freopen("test1.txt", "r", stdin);
    //freopen("test2.txt", "r", stdin);
    //freopen("test3.txt", "r", stdin);
    cin >> N >> D;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            char Cell;
            cin >> Cell;
            Grid[y][x] = (Cell != '#');
            if (Cell == 'S') Starts.push_back({x, y});
        }
    }
    FFRockDist();
    FFPsblCenters();
    cout << FFReachable() << "\n";
    return 0;
}
