#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

ofstream fout("closing.out");
ifstream fin("closing.in");

int Dfs(const unordered_map<int, unordered_set<int> >& Paths, unordered_set<int>& Visited, int Barn) {
    int Visits = 1;
    Visited.insert(Barn);
    for (int i : Paths.at(Barn)) {
        if (Visited.count(i) == 0) Visits += Dfs(Paths, Visited, i);
    }
    return Visits;
}

int main() {
    int N, M;
    unordered_set<int> Visited;
    unordered_map<int, unordered_set<int> > Paths;
    fin >> N >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        if (Paths.count(a) == 0) Paths[a] = {b};
        else Paths[a].insert(b);
        if (Paths.count(b) == 0) Paths[b] = {a};
        else Paths[b].insert(a);
    }
    if (Dfs(Paths, Visited, Paths.begin()->first) == N) fout << "YES\n";
    else fout << "NO\n";
    for (int i = 1; i < N; i++) {
        int ClosedBarn;
        fin >> ClosedBarn;
        Visited.clear();
        for (int j : Paths[ClosedBarn]) Paths[j].erase(ClosedBarn);
        Paths.erase(ClosedBarn);
        if (Dfs(Paths, Visited, Paths.begin()->first) == N - i) fout << "YES\n";
        else fout << "NO\n";
    }
    return 0;
}
