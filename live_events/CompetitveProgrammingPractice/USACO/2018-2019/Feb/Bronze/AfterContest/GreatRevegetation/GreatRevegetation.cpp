#include <fstream>
#include <vector>
#include <set>

using namespace std;

ofstream fout("revegetate.out");
ifstream fin("revegetate.in");

int main() {
    int N, M;
    fin >> N >> M;
    vector<vector<int> > Graph(N);
    vector<int> GrassType(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        fin >> a >> b;
        a--;
        b--;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }
    for (int i = 0; i < N; i++) {
        set<int> Possible = {1, 2, 3, 4};
        for (int j : Graph[i]) {
            if (j < i) Possible.erase(GrassType[j]);
        }
        GrassType[i] = *Possible.begin();
    }
    for (int i : GrassType) fout << i;
    fout << "\n";
    return 0;
}
