#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("clocktree.out");
ifstream fin("clocktree.in");

void Dfs(const vector<vector<int> >& Tree, vector<int>& Clocks, const int Node, const int Parent, const int Root) {
    if (Parent != -1) Clocks[Node] = (Clocks[Node] + 1) % 12;
    for (int i : Tree[Node]) {
        if (i != Parent) Dfs(Tree, Clocks, i, Node, Root);
    }
    if (Parent != -1) {
        Clocks[Parent] = (Clocks[Parent] + 13 - Clocks[Node]) % 12;
        Clocks[Node] = 0;
    }
    return;
}

bool IsPossibleRoot(const vector<vector<int> >& Tree, vector<int> Clocks, const int Root) {
    Dfs(Tree, Clocks, Root, -1, Root);
    return (Clocks[Root] == 0 or Clocks[Root] == 1);
}

int main() {
    int N, Count = 0;
    fin >> N;
    vector<int> Clocks(N);
    vector<vector<int> > Tree(N);
    for (int i = 0; i < N; i++) fin >> Clocks[i];
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        Tree[a].push_back(b);
        Tree[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        if (IsPossibleRoot(Tree, Clocks, i)) Count++;
    }
    fout << Count << "\n";
    return 0;
}
