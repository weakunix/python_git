#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<int> Parent;

int GetParent(const int Node) {
    if (Parent[Node] < 0) return Node;
    Parent[Node] = GetParent(Parent[Node]);
    return Parent[Node];
}

void Merge(const int Cur, const int New) {
    int a = GetParent(Cur), b = GetParent(New);
    Parent[b] += Parent[a];
    Parent[a] = b;
    return;
}

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    int N, M, LastOpen;
    cin >> N >> M;
    vector<int> ClosingOrd;
    vector<bool> Ans(N);
    vector<unordered_set<int> > Edges(N);
    Parent.resize(N, -1);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Edges[a].insert(b);
        Edges[b].insert(a);
    }
    for (int i = 0; i < N; i++) {
        int Cur;
        cin >> Cur;
        Cur--;
        ClosingOrd.push_back(Cur);
        for (int j : Edges[Cur]) Edges[j].erase(Cur);
    }
    LastOpen = ClosingOrd[N - 1];
    Ans[N - 1] = true;
    for (int i = N - 2; i >= 0; i--) {
        int Cur = ClosingOrd[i];
        for (int j : Edges[Cur]) {
            if (GetParent(Cur) != GetParent(j)) {
                if (GetParent(Cur) == LastOpen) Merge(j, Cur);
                else Merge(Cur, j);
            }
        }
        Ans[i] = (Parent[LastOpen] == i - N);
    }
    for (bool b : Ans) {
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
