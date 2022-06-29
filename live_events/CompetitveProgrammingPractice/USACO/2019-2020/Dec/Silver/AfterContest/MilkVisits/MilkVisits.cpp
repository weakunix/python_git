#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("milkvisits.out");
ifstream fin("milkvisits.in");

void Dfs(const vector<vector<int> >& Tree, vector<bool>& Visited, const string& CowSeq, vector<int>& ConComps, const int ConCompCount, const int Node) {
    Visited[Node] = true;
    ConComps[Node] = ConCompCount;
    for (int i : Tree[Node]) {
        if (not Visited[i] and (CowSeq[i] == CowSeq[Node])) Dfs(Tree, Visited, CowSeq, ConComps, ConCompCount, i);
    }
    return;
}

int main() {
    int N, M, ConCompCount = 0;
    string CowSeq, Ans = "";
    fin >> N >> M >> CowSeq;
    vector<int> ConComps(N);
    vector<bool> Visited(N);
    vector<vector<int> > Tree(N);
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        Tree[x].push_back(y);
        Tree[y].push_back(x);
    }
    for (int i = 0; i < N; i++) {
        if (not Visited[i]) {
            ConCompCount++;
            Dfs(Tree, Visited, CowSeq, ConComps, ConCompCount, i);
        }
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        char c;
        fin >> a >> b >> c;
        a--;
        b--;
        if (ConComps[a] != ConComps[b] or CowSeq[a] == c) Ans += '1';
        else Ans += '0';
    }
    fout << Ans << "\n";
    return 0;
}
