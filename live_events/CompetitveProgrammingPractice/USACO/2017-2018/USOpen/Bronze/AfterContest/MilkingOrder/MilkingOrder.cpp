#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

ofstream fout("milkorder.out");
ifstream fin("milkorder.in");

#define all(v) v.begin(), v.end()

int main() {
    int N, M, K, Cow, Spot, SpotsNeeded = 0, CurStart = 0;
    vector<int> SpotsEmpty;
    unordered_map<int, int> ReservedSpots;
    fin >> N >> M >> K;
    vector<int> Ord(N), Hrchy(M);
    for (int i = 0; i < M; i++) fin >> Hrchy[i];
    for (int i = 0; i < K; i++) {
        fin >> Cow >> Spot;
        if (Cow == 1) {
            fout << Spot << "\n";
            return 0;
        }
        ReservedSpots[Cow] = Spot;
        Ord[Spot - 1] = Cow;
    }
    if (count(all(Hrchy), 1) == 0) {
        for (int i : Hrchy) {
            if (ReservedSpots.count(i) == 0) SpotsNeeded++;
            else {
                for (int k = CurStart; k < ReservedSpots[i] - 1; k++) {
                    if (Ord[k] == 0) SpotsEmpty.push_back(k);
                }
                if (SpotsEmpty.size() > SpotsNeeded) {
                    fout << SpotsEmpty[0] + 1 << "\n";
                    return 0;
                }
                CurStart = ReservedSpots[i];
                SpotsNeeded = 0;
                SpotsEmpty.clear();
            }
        }
        for (int i = CurStart; i < N; i++) {
            if (Ord[i] == 0) {
                fout << i + 1 << "\n";
                return 0;
            }
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            if (ReservedSpots.count(Hrchy[0]) == 0) {
                if (Ord[i] == 0) {
                    if (Hrchy[0] == 1) {
                        fout << i + 1 << "\n";
                        return 0;
                    }
                    Hrchy.erase(Hrchy.begin());
                }
            }
            if (Ord[i] == Hrchy[0]) Hrchy.erase(Hrchy.begin());
        }
    }
    return 1;
}
