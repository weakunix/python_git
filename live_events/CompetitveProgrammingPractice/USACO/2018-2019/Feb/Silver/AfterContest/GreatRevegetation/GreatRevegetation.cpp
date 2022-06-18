#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("revegetate.out");
ifstream fin("revegetate.in");

bool Dfs(const vector<vector<int> >& Same, const vector<vector<int> >& Diff, vector<int>& PlantTypes, const int PlantType, const int Cur) {
    PlantTypes[Cur] = PlantType;
    for (int i : Same[Cur]) {
        if (PlantTypes[i] == 0) {
            if (not Dfs(Same, Diff, PlantTypes, PlantType, i)) return false;
        }
        else {
            if (PlantTypes[i] != PlantType) return false;
        }
    }
    for (int i : Diff[Cur]) {
        if (PlantTypes[i] == 0) {
            if (not Dfs(Same, Diff, PlantTypes, PlantType * -1, i)) return false;
        }
        else {
            if (PlantTypes[i] == PlantType) return false;
        }
    }
    return true;
}

int main() {
    int N, M, ConCompNum = 0;
    fin >> N >> M;
    vector<int> PlantTypes(N);
    vector<vector<int> > Same(N), Diff(N);
    for (int i = 0; i < M; i++) {
        char Type;
        int a, b;
        fin >> Type >> a >> b;
        a--;
        b--;
        if (Type == 'S') {
            Same[a].push_back(b);
            Same[b].push_back(a);
        }
        else {
            Diff[a].push_back(b);
            Diff[b].push_back(a);
        }
    }
    for (int i = 0; i < N; i++) {
        if (PlantTypes[i] == 0) {
            if (not Dfs(Same, Diff, PlantTypes, 1, i)) {
                fout << "0\n";
                return 0;
            }
            ConCompNum++;
        }
    }
    fout << "1";
    for (int i = 0; i < ConCompNum; i++) fout << "0";
    fout << "\n";
    return 0;
}
