#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, bool> simps;
typedef pair<int, simps> threesome;

#define all(v) v.begin(), v.end()
#define sec second.first
#define third second.second

int A, B, n, m;
ll Ans = 0;
vector<int> Vert, Horiz, Parent;
vector<threesome> Edges;

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
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    cin >> A >> B >> n >> m;
    Vert.resize(n);
    Horiz.resize(m);
    Parent.resize((n + 1) * (m + 1), -1);
    for (int i = 0; i < n; i++) cin >> Vert[i];
    for (int i = 0; i < m; i++) cin >> Horiz[i];
    
    Vert.push_back(0);
    Horiz.push_back(0);

    Vert.push_back(A);
    Horiz.push_back(B);

    sort(all(Vert));
    sort(all(Horiz));

    for (int i = 0; i <= n; i++) Edges.push_back({Vert[i + 1] - Vert[i], {i, true}});
    for (int i = 0; i <= m; i++) Edges.push_back({Horiz[i + 1] - Horiz[i], {i * (n + 1), false}});

    sort(all(Edges));
    
    for (const threesome& t : Edges) {
        int Weight = t.first, StartNode = t.sec;
        bool IsVert = t.third;
        if (IsVert) {
            for (int y = 0; y <= m; y++) {
                int Node = StartNode + y * (n + 1);
                if (Merge(StartNode, Node)) Ans += Weight;
            }
        }
        else {
            for (int x = 0; x <= n; x++) {
                int Node = StartNode + x;
                if (Merge(StartNode, Node)) Ans += Weight;
            }
        }
    }

    cout << Ans << "\n";

    return 0;
}
