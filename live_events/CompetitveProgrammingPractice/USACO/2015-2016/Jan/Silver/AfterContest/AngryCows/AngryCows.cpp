#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define rall(v) v.rbegin(), v.rend()

ofstream fout("angry.out");
ifstream fin("angry.in");

bool CanDestroyAll(vector<int> Haybales, int R, int K) {
    for (int i = 0; i < K; i++) {
        int First = Haybales.back();
        while (Haybales.size() > 0 and Haybales.back() - First <= 2 * R) Haybales.pop_back();
        if (Haybales.size() == 0) return true;
    }
    return false;
}

int main() {
    int N, K, Low = 0, High = 1e9, Ans = -1;
    fin >> N >> K;
    vector<int> Haybales(N);
    for (int i = 0; i < N; i++) fin >> Haybales[i];
    sort(rall(Haybales));
    while (Low <= High) {
        int Mid = Low + (High - Low + 1) / 2;
        if (CanDestroyAll(Haybales, Mid, K)) {
            Ans = Mid;
            High = Mid - 1;
        }
        else Low = Mid + 1;
    }
    assert(Ans > -1);
    fout << Ans << "\n";
    return 0;
}
