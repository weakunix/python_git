#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

ofstream fout("mootube.out");
ifstream fin("mootube.in");

int Dfs(const vector<vector<simps> >& Tree, const int Node, const int Parent, const int K) {
    int Count = 1;
    for (const simps& s : Tree[Node]) {
        if (s.first != Parent and s.second >= K) Count += Dfs(Tree, s.first, Node, K);
    }
    return Count;
}

int main() {
    int N, Q;
    fin >> N >> Q;
    vector<vector<simps> > Tree(N);
    for (int i = 0; i < N - 1; i++) {
        int p, q, r;
        fin >> p >> q >> r;
        p--;
        q--;
        Tree[p].push_back({q, r});
        Tree[q].push_back({p, r});
    }
    for (int i = 0; i < Q; i++) {
        int K, Root;
        fin >> K >> Root;
        Root--;
        fout << Dfs(Tree, Root, -1, K) - 1 << "\n";
    }
    return 0;
}
