#include <fstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

ofstream fout("angry.out");
ifstream fin ("angry.in");

int SimulateExplosion(unordered_set<int> HaybalesRemain, unordered_set<int> JustExploded, int Radius) {
    if (JustExploded.size() == 0) return HaybalesRemain.size(); 
    unordered_set<int> Exploded, PossibleExplode;
    for (int i : JustExploded) {
        for (int k = i - Radius; k <= i + Radius; k++) PossibleExplode.insert(k);
    }
    for (int i : HaybalesRemain) {
        if (PossibleExplode.count(i) > 0) Exploded.insert(i);
    }
    for (int i : Exploded) HaybalesRemain.erase(i);
    return SimulateExplosion(HaybalesRemain, Exploded, Radius + 1);
}

int main() {
    int N, Best = 0;
    unordered_set<int> Haybales;
    fin >> N;
    for (int i = 0; i < N; i++) {
        int Loc;
        fin >> Loc;
        Haybales.insert(Loc);
    }
    for (int i : Haybales) {
        unordered_set<int> TempHaybales = Haybales;
        TempHaybales.erase(i);
        int HaybalesDestroyed = Haybales.size() - SimulateExplosion(TempHaybales, {i}, 1);
        Best = max(HaybalesDestroyed, Best);
    }
    fout << Best << "\n";
    return 0;
}
