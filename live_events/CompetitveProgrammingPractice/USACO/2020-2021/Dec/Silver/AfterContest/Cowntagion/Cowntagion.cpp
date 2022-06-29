#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Dfs(const vector<vector<int> >& Tree, const int Node, const int Parent) {
    int Days = 0, CurCows = 1, TarCows = Tree[Node].size() + (Node == 0);
    while (CurCows < TarCows) {
        CurCows *= 2;
        Days++;
    }
    for (int i : Tree[Node]) {
        if (i != Parent) Days += Dfs(Tree, i, Node);
    }
    return Days;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int> > Tree(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        Tree[a].push_back(b);
        Tree[b].push_back(a);
    }
    cout << Dfs(Tree, 0, -1) + N - 1 << "\n";
    return 0;
}
