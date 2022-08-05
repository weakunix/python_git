#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> Parent;
vector<set<int> > Admirers;

int GetRoot(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetRoot(Parent[Node]);
    return Parent[Node];
}

void Merge(const int a, const int b) {
    Parent[a] = b;
    for (int i : Admirers[a]) Admirers[b].insert(i);
    Admirers[a].clear();
    return;
}

void StartMerging(int Node) {
    assert(Node == GetRoot(Node) or Admirers[Node].size() == 0);
    Node = GetRoot(Node);
    if (Admirers[Node].size() <= 1) return;
    int Start = *Admirers[Node].begin();
    if (Admirers[Node].count(Node) > 0) Start = Node;
    for (int i : Admirers[Node]) {
        if (GetRoot(i) != GetRoot(Start)) Merge(GetRoot(i), GetRoot(Start));
    }
    if (Node != Start) {
        Admirers[Node].clear();
        Admirers[Node].insert(Start);
        StartMerging(Start);
    }
    return;
}

int main() {
    freopen("fcolor.in", "r", stdin);
    freopen("fcolor.out", "w", stdout);

    int N, M, Count = -1;
    cin >> N >> M;
    Admirers.resize(N);
    Parent.resize(N, -1e9);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Admirers[a].insert(b);
    }

    for (int i = 0; i < N; i++) StartMerging(i);

    for (int i = 0; i < N; i++) {
        int CurRoot = GetRoot(i);
        if (Parent[CurRoot] == -1e9) {
            Parent[CurRoot] = Count;
            Count--;
        }
        cout << -Parent[CurRoot] << "\n";
    }

    return 0;
}
