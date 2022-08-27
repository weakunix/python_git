#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

int N, Ans = 0;
vector<int> NodePrevOccur, Parent;
vector<threesome> Edges;

void PrevPortal(const int Portal, const int Node) {
    if (NodePrevOccur[Portal] == -1) {
        NodePrevOccur[Portal] = Node;
        return;
    }
    Edges.push_back({0, {NodePrevOccur[Portal], Node}});
    return;
}

int GetRoot(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

bool Merge(int a, int b) {
    a = GetRoot(a);
    b = GetRoot(b);
    if (a == b) return false;
    if (Parent[a] < Parent[b]) swap(a, b);
    Parent[b] += Parent[a];
    Parent[a] = b;
    return true;
}

int main() {
    //freopen("test.in", "r", stdin);

    cin >> N;
    NodePrevOccur.resize(2 * N, -1);
    Parent.resize(4 * N, -1);

    for (int i = 0; i < N; i++) {
        int c, w, x, y, z;
        cin >> c >> w >> x >> y >> z;
        w--;
        x--;
        y--;
        z--;
        Edges.push_back({0, {4 * i, 4 * i + 1}});
        Edges.push_back({0, {4 * i + 2, 4 * i + 3}});
        Edges.push_back({c, {4 * i, 4 * i + 3}});
        PrevPortal(w, 4 * i);
        PrevPortal(x, 4 * i + 1);
        PrevPortal(y, 4 * i + 2);
        PrevPortal(z, 4 * i + 3);
    }
    
    sort(all(Edges));

    for (const threesome& t : Edges) {
        if (Merge(t.sec, t.third)) Ans += t.first;
    }

    cout << Ans << "\n";

    return 0;
}
