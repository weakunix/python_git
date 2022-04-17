#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("outofplace.out");
ifstream fin("outofplace.in");

int main() {
    int N, OutPlace = 0;
    set<int> Swaps;
    fin >> N;
    vector<int> Heights(N);
    for (int i = 0; i < N; i++) fin >> Heights[i];
    for (int i = 0; i < N; i++) {
        vector<int> TempHeights = Heights;
        TempHeights.erase(TempHeights.begin() + i);
        if (is_sorted(all(TempHeights))) {
            OutPlace = i;
            break;
        }
    }
    for (int i = 0; i < OutPlace; i++) {
        if (Heights[i] > Heights[OutPlace]) Swaps.insert(Heights[i]);
    }
    for (int i = OutPlace + 1; i < N; i++) {
        if (Heights[i] < Heights[OutPlace]) Swaps.insert(Heights[i]);
    }
    fout << Swaps.size() << "\n";
    return 0;
}
