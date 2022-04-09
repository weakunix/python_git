/*
Test outputs

1:
3
*/

#include <fstream>
#include <vector>
#include <unordered_map>

//#include <iostream>

using namespace std;

ofstream fout("badmilk.out");
ifstream fin("badmilk.in");

int main() {
    int N, M, D, S, p, m, t, MedNeeded = 0;
    bool Possible;
    unordered_map<int, unordered_map<int, int> > MilkHist;
    unordered_map<int, int> SickHist;
    fin >> N >> M >> D >> S;
    for (int i = 0; i < D; i++) {
        fin >> p >> m >> t;
        if (MilkHist.count(m) == 0 or MilkHist[m].count(p) == 0 or t < MilkHist[m][p]) MilkHist[m][p] = t;
    }
    for (int i = 0; i < S; i++) {
        fin >> p >> t;
        SickHist[p] = t;
    }
    for (auto it = MilkHist.begin(); it != MilkHist.end(); it++) {
        for (auto it2 = SickHist.begin(); it2 != SickHist.end(); it2++) {
            Possible = true;
            if (it->second.count(it2->first) == 0 or it->second[it2->first] >= it2->second) {
                Possible = false;
                break;
            }
        }
        if (Possible and it->second.size() > MedNeeded) MedNeeded = it->second.size();
    }
    fout << MedNeeded << "\n";
    return 0;
}
