#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<simps, int> threesome;

int Bfs(const vector<vector<bool> >& Space, const int N, const int M, const int Sx, const int Sy, const int Ex, const int Ey) {
    deque<threesome> CellDeque;
    set<simps> Visited = {{Sx, Sy}};
    CellDeque.push_back({{Sx, Sy}, 0});
    while (not CellDeque.empty()) {
        int CurX = CellDeque.front().first.first, CurY = CellDeque.front().first.second, CurCount = CellDeque.front().second, CurGravDir;
        CellDeque.pop_front();
        if (CurCount % 2 == 0) CurGravDir = 1;
        else CurGravDir = -1;
        if (CurX > 0 and Space[CurY][CurX - 1]) {
            int x = CurX - 1, y = CurY;
            if (x == Ex and y == Ey) return CurCount;
            while ((y > 0 and y < N - 1) and Space[y + CurGravDir][x]) {
                y += CurGravDir;
                if (x == Ex and y == Ey) return CurCount;
            }
            if ((y > 0 and y < N - 1) and Visited.count({x, y}) == 0) {
                Visited.insert({x, y});
                CellDeque.push_front({{x, y}, CurCount});
            }
        }
        if (CurX < M - 1 and Space[CurY][CurX + 1]) {
            int x = CurX + 1, y = CurY;
            if (x == Ex and y == Ey) return CurCount;
            while ((y > 0 and y < N - 1) and Space[y + CurGravDir][x]) {
                y += CurGravDir;
                if (x == Ex and y == Ey) return CurCount;
            }
            if ((y > 0 and y < N - 1) and Visited.count({x, y}) == 0) {
                Visited.insert({x, y});
                CellDeque.push_front({{x, y}, CurCount});
            }
        }
        CurCount++;
        while ((CurY > 0 and CurY < N - 1) and Space[CurY - CurGravDir][CurX]) {
            CurY -= CurGravDir;
            if (CurX == Ex and CurY == Ey) return CurCount;
        }
            if ((CurY > 0 and CurY < N - 1) and Visited.count({CurX, CurY}) == 0) {
                Visited.insert({CurX, CurY});
                CellDeque.push_back({{CurX, CurY}, CurCount});
            }
    }
    return -1;
}

int main() {
    freopen("gravity.in", "r", stdin);
    freopen("gravity.out", "w", stdout);
    int N, M, Sx, Sy, Ex, Ey;
    cin >> N >> M;
    vector<vector<bool> > Space;
    for (int y = 0; y < N; y++) {
        vector<bool> SpaceRow;
        for (int x = 0; x < M; x++) {
            char Cell;
            cin >> Cell;
            if (Cell == '#') {
                SpaceRow.push_back(false);
                continue;
            }
            SpaceRow.push_back(true);
            if (Cell == 'C') {
                Sx = x;
                Sy = y;
            }
            else if (Cell == 'D') {
                Ex = x;
                Ey = y;
            }
        }
        Space.push_back(SpaceRow);
    }
    while (Sy < N - 1 and Space[Sy + 1][Sx]) {
        Sy++;
        if (Sx == Ex and Sy == Ey) {
            cout << "0\n";
            return 0;
        }
    }
    if (Sy == N - 1) {
        cout << "-1\n";
        return 0;
    }
    cout << Bfs(Space, N, M, Sx, Sy, Ex, Ey) << "\n";
    return 0;
}
