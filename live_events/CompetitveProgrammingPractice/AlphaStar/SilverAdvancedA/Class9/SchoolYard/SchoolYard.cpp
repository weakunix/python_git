#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> p4i;

#define fir first.first
#define sec first.second
#define third second.first
#define fourth second.second

int CoordMap(unordered_map<int, int>& Map, const set<int>& Vals) {
    int Index = 0;
    for (int i : Vals) {
        Map[i] = Index;
        Index++;
    }
    return Index;
}

void Input(int& N, int& S, int& X, int& Y, vector<pii>& Students, vector<p4i>& Walls) {
    set<int> XVals, YVals;
    unordered_map<int, int> XMap, YMap;
    cin >> N >> S;
    for (int i = 0; i < N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        XVals.insert(a);
        YVals.insert(b);
        XVals.insert(c);
        YVals.insert(d);
        Walls.push_back({{a, b}, {c, d}});
    }
    for (int i = 0; i < S; i++) {
        int x, y;
        cin >> x >> y;
        XVals.insert(x);
        YVals.insert(y);
        Students.push_back({x, y});
    }
    X = 2 * CoordMap(XMap, XVals) + 4;
    Y = 2 * CoordMap(YMap, YVals) + 4;
    for (p4i& p : Walls) {
        p.fir = 2 * XMap[p.fir] + 2;
        p.sec = 2 * YMap[p.sec] + 2;
        p.third = 2 * XMap[p.third] + 2;
        p.fourth = 2 * YMap[p.fourth] + 2;
    }
    for (pii& p : Students) {
        p.first = 2 * XMap[p.first] + 3;
        p.second = 2 * YMap[p.second] + 3;
    }
    return;
}

int FloodFill(vector<vector<int> >& CellType, const int X, const int Y, const int x, const int y) {
    int Count = 0, DirX[4] = {1, 0, -1, 0}, DirY[4] = {0, 1, 0, -1};
    queue<pii> CellQueue;
    CellQueue.push({x, y});
    if (CellType[y][x] == 2) Count++;
    CellType[y][x] = 0;
    while (CellQueue.size() > 0) {
        int CurX = CellQueue.front().first, CurY = CellQueue.front().second;
        CellQueue.pop();
        for (int i = 0; i < 4; i++) {
            int NewX = CurX + DirX[i], NewY = CurY + DirY[i];
            if ((NewX >= 0 and NewX < X) and (NewY >= 0 and NewY < Y)) {
                if (CellType[NewY][NewX] > 0) {
                    NewX += DirX[i], NewY += DirY[i];
                    if ((NewX >= 0 and NewX < X) and (NewY >= 0 and NewY < Y)) {
                        if (CellType[NewY][NewX] > 0) {
                            if (CellType[NewY][NewX] == 2) Count++;
                            CellType[NewY][NewX] = 0;
                            CellQueue.push({NewX, NewY});
                        }
                    }
                }
            }
        }
    }
    return Count;
}

int main() {
    int N, S, X, Y, Ans = 0;
    vector<pii> Students;
    vector<p4i> Walls;
    Input(N, S, X, Y, Students, Walls);
    vector<vector<int> > CellType;
    for (int i = 0; i < Y; i++) {
        vector<int> CellTypeRow(X, 1);
        CellType.push_back(CellTypeRow);
    }
    for (const p4i& p : Walls) {
        int a = p.fir, b = p.sec, c = p.third, d = p.fourth;
        for (int y = min(b, d); y <= max(b, d); y++) {
            for (int x = min(a, c); x <= max(a, c); x++) CellType[y][x] = 0;
        }
    }
    for (const pii& p : Students) {
        int x = p.first, y = p.second;
        assert(CellType[y][x] == 1);
        CellType[y][x] = 2;
    }
    for (int y = 1; y < Y; y += 2) {
        for (int x = 1; x < X; x += 2) {
            if (CellType[y][x] > 0) Ans = max(FloodFill(CellType, X, Y, x, y), Ans);
        }
    }
    cout << Ans << "\n";
    return 0;
}
