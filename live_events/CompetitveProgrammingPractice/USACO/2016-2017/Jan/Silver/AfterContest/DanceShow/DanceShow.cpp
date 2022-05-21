#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("cowdance.out");
ifstream fin("cowdance.in");

bool CanFinishOnTime(int K, vector<int> Dances, int T) {
    multiset<int> Dancing;
    for (int i = 0; i < K; i++) {
        assert(Dances.size() > 0);
        Dancing.insert(Dances.back());
        Dances.pop_back();
    }
    while (Dances.size() > 0) {
        int CurTime = *Dancing.begin(), Count = 0;
        while (Dancing.size() > 0 and *Dancing.begin() == CurTime) {
            Dancing.erase(Dancing.begin());
            Count++;
        }
        assert(Count > 0);
        for (int i = 0; i < Count; i++) {
            if (Dances.size() == 0) break;
            Dancing.insert(CurTime + Dances.back());
            Dances.pop_back();
        }
    }
    assert(Dancing.size() > 0);
    auto it = Dancing.end();
    it--;
    return *it <= T;
}

int main() {
    int N, T, Low = 1, High, Ans = 0;
    fin >> N >> T;
    High = N;
    vector<int> Dances(N);
    for (int i = 0; i < N; i++) fin >> Dances[i];
    reverse(all(Dances));
    while (High >= Low) {
        int Mid = Low + (High - Low + 1) / 2;
        if (CanFinishOnTime(Mid, Dances, T)) {
            Ans = Mid;
            High = Mid - 1;
        }
        else Low = Mid + 1;
    }
    assert(Ans > 0);
    fout << Ans << "\n";
    return 0;
}
