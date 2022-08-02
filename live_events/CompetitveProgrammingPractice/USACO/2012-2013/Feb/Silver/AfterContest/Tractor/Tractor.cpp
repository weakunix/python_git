#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

vector<int> Parent;

int GetRoot(const int Node) {
    assert(Parent[Node] != Node);
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

int Merge(int a, int b) {
    if (Parent[a] < Parent[b]) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;
    return -Parent[b];
}

int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);

    int N, Tar;
    vector<threesome> Edges;
    cin >> N;
    vector<vector<int> > Grid(N);
    Tar = (N * N + 1) / 2;
    Parent.resize(N * N, -1);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            int Cur;
            cin >> Cur;
            Grid[y].push_back(Cur);
            if (x > 0) Edges.push_back({abs(Grid[y][x - 1] - Cur), {y * N + x, y * N + x - 1}});
            if (y > 0) Edges.push_back({abs(Grid[y - 1][x] - Cur), {y * N + x, y * N + x - N}});
        }
    }
    sort(all(Edges));
    for (const threesome& t : Edges) {
        int D = t.first, a = t.sec, b = t.third;
        assert(a >= 0 and a < N * N);
        assert(b >= 0 and b < N * N);
        if (GetRoot(a) != GetRoot(b)) {
            if (Merge(GetRoot(a), GetRoot(b)) >= Tar) {
                cout << D << "\n";
                return 0;
            }
        }
    }
    assert(false);
    return 1;
}
