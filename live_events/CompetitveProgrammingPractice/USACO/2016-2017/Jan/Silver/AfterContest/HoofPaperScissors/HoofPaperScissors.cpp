#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("hps.out");
ifstream fin("hps.in");

int main() {
    int N, MaxWins = 0;
    vector<int> PreH = {0}, PreP = {0}, PreS = {0};
    fin >> N;
    for (int i = 1; i <= N; i++) {
        PreH.push_back(PreH.back());
        PreP.push_back(PreP.back());
        PreS.push_back(PreS.back());
        char Gest;
        fin >> Gest;
        if (Gest == 'H') PreH[i]++;
        else if (Gest == 'P') PreP[i]++;
        else PreS[i]++;
    }
    for (int i = 1; i <= N; i++) MaxWins = max(max({PreH[i], PreP[i], PreS[i]}) + max({PreH[N] - PreH[i], PreP[N] - PreP[i], PreS[N] - PreS[i]}), MaxWins);
    fout << MaxWins << "\n";
    return 0;
}
