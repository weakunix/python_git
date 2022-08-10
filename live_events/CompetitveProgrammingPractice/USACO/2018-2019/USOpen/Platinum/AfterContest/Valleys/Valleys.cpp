#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int N;
ll Ans = 0;
vector<int> Parent(1e6, -1), HoleCount(1e6), DirX = {1, 0, -1, 0}, DirY = {0, 1, 0, -1};
vector<simps> Points;
vector<vector<int> > Grid;

bool HeightCmp(const simps& a, const simps& b) {
    return Grid[a.second][a.first] < Grid[b.second][b.first];
}

void InputAndOrder() {
    cin >> N;
    Grid.resize(N + 2);
    for (int i = 0; i < N + 2; i++) Grid[i].resize(N + 2, 1e7);
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            int CurHeight;
            cin >> CurHeight;
            CurHeight--;
            Grid[y][x] = CurHeight;
            Points.push_back({x, y});
        }
    }
    sort(all(Points), HeightCmp);
    return;
}

int GetRoot(const int Node) {
    if (Node == 1e7) return -1;
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

void Merge(int a, int b) {
    if (Parent[a] < Parent[b]) swap(a, b);
    HoleCount[b] += HoleCount[a];
    HoleCount[a] = 0;
    Parent[b] += Parent[a];
    Parent[a] = b;
    return;
}

int SetHoleCount(const int x, const int y, const int Node) {
    int Res = 0;
    vector<int> EdgeX = {x, x - 1, x, x + 1, x}, EdgeY = {y - 1, y, y + 1, y, y - 1}, CornerX = {x - 1, x - 1, x + 1, x + 1}, CornerY = {y - 1, y + 1, y + 1, y - 1};
    map<int, int> Surrounding;
    for (int i = 0; i < 4; i++) {
        if (GetRoot(Grid[EdgeY[i]][EdgeX[i]]) == GetRoot(Grid[EdgeY[i + 1]][EdgeX[i + 1]]) and GetRoot(Grid[EdgeY[i]][EdgeX[i]]) == GetRoot(Grid[CornerY[i]][CornerX[i]])) continue;
        Surrounding[GetRoot(Grid[EdgeY[i]][EdgeX[i]])]++;
    }
    if (Surrounding.size() == 0) return -1;
    assert(Surrounding.size() <= 4);
    for (auto it : Surrounding) {
        if (it.first != -1) Res += it.second - 1;
    }
    return Res;
}

int main() {
    freopen("valleys.in", "r", stdin);
    freopen("valleys.out", "w", stdout);

    InputAndOrder();
    
    for (const simps& s : Points) {
        int x = s.first, y = s.second, val = Grid[y][x];
        HoleCount[val] += SetHoleCount(x, y, val);
        for (int i = 0; i < 4; i++) {
            int curx = x + DirX[i], cury = y + DirY[i], curval = Grid[cury][curx];
            if (curval < val and GetRoot(val) != GetRoot(curval)) Merge(GetRoot(val), GetRoot(curval));
        }
        assert(HoleCount[GetRoot(val)] >= 0);
        if (HoleCount[GetRoot(val)] == 0) Ans -= Parent[GetRoot(val)];
    }

    cout << Ans << "\n";

    return 0;
}
