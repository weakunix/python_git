#include <fstream>
#include <vector>

using namespace std;

ofstream fout("bcount.out");
ifstream fin("bcount.in");

int main() {
    int N, Q;
    vector<int> PreH = {0}, PreG = {0}, PreJ = {0};
    fin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        int Type;
        fin >> Type;
        PreH.push_back(PreH.back());
        PreG.push_back(PreG.back());
        PreJ.push_back(PreJ.back());
        if (Type == 1) PreH[i]++;
        else if (Type == 2) PreG[i]++;
        else PreJ[i]++;
    }
    for (int i = 0; i < Q; i++) {
        int a, b;
        fin >> a >> b;
        fout << PreH[b] - PreH[a - 1] << " " << PreG[b] - PreG[a - 1] << " " << PreJ[b] - PreJ[a - 1] << "\n";
    }
    return 0;
}
