#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<simps, int> threesome;

int Bfs(const unordered_map<int, vector<int> >& XToY, const unordered_map<int, vector<int> >& YToX, const int Lx, const int Ly, const int Bx, const int By) {
    queue<threesome> PtQueue;
    set<simps> Visited;
    PtQueue.push({{Lx, Ly}, 0});
    Visited.insert({Lx, Ly});
    while (not PtQueue.empty()) {
        int CurX = PtQueue.front().first.first, CurY = PtQueue.front().first.second, CurCount = PtQueue.front().second;
        PtQueue.pop();
        if (CurX == Bx and CurY == By) return CurCount - 1;
        for (int y : XToY.at(CurX)) {
            if (y != CurY) {
                if (Visited.count({CurX, y}) > 0) break;
                Visited.insert({CurX, y});
                PtQueue.push({{CurX, y}, CurCount + 1});
            }
        }
        for (int x : YToX.at(CurY)) {
            if (x != CurX) {
                if (Visited.count({x, CurY}) > 0) break;
                Visited.insert({x, CurY});
                PtQueue.push({{x, CurY}, CurCount + 1});
            }
        }
    }
    return -1;
}

int main() {
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    int N, Lx, Ly, Bx, By;
    unordered_map<int, vector<int> > XToY, YToX;
    cin >> N >> Lx >> Ly >> Bx >> By;
    XToY[Lx].push_back(Ly);
    YToX[Ly].push_back(Lx);
    XToY[Bx].push_back(By);
    YToX[By].push_back(Bx);
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;
        XToY[x].push_back(y);
        YToX[y].push_back(x);
    }
    cout << Bfs(XToY, YToX, Lx, Ly, Bx, By) << "\n";
    return 0;
}
