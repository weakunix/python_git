#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()

ofstream fout("cowpatibility.out");
ifstream fin("cowpatibility.in");

struct Subset {
    int Size;
    int SubsetVals[5];
};


bool operator< (const Subset& a, const Subset& b) {
    for (int i = 0; i < 5; i++) {
        if (a.SubsetVals[i] < b.SubsetVals[i]) return true;
        if (a.SubsetVals[i] > b.SubsetVals[i]) return false;
    }
    return false;
}

void AllPermutations(map<Subset, int>& Preferences, const vector<int>& Cur) {
    for (int i = 1; i < 32; i++) {
        int CurPermutationVal = i;
        Subset CurPermutation = {0, {0, 0, 0, 0, 0}};
        for (int j = 0; j < 5; j++) {
            if (CurPermutationVal % 2 == 1) {
                assert(CurPermutation.Size < 5);
                CurPermutation.SubsetVals[CurPermutation.Size] = Cur[j];
                CurPermutation.Size++;
            }
            CurPermutationVal /= 2;
        }
        CurPermutation.Size %= 2;
        if (CurPermutation.Size == 0) CurPermutation.Size = -1;
        Preferences[CurPermutation]++;;
    }
    return;
}

int TotalPairs(const int N) {
    ll Ans = N;
    Ans *= N - 1;
    Ans /= 2;
    return (int) Ans;
}

int main() {
    int N, Ans = 0;
    map<Subset, int> Preferences;
    fin >> N;
    for (int i = 0; i < N; i++) {
        vector<int> Cur(5);
        for (int j = 0; j < 5; j++) fin >> Cur[j];
        sort(all(Cur));
        AllPermutations(Preferences, Cur);
    }
    for (const auto& p : Preferences) Ans += TotalPairs(p.second) * p.first.Size;
    fout << TotalPairs(N) - Ans << "\n";
    return 0;
}
