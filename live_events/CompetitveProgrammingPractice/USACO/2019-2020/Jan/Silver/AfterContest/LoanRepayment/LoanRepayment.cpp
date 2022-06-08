#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

ofstream fout("loan.out");
ifstream fin("loan.in");

bool IsValidX(ll N, ll K, ll M, ll X) {
    if (X == 1)
        fout << "";
    while (N > 0 and K > 0) {
        ll Y = N / X, Lowest = X * Y;
        if (Y < M) break;
        ll NumPossible = (N - Lowest) / Y + 1;
        N -= NumPossible * Y;
        K -= NumPossible;
    }
    if (N <= 0) return K >= 0;
    if (N % M != 0) K--;
    K -= N / M;
    return K >= 0;
}

int main() {
    ll N, K, M, Low = 0, High = 1e12;
    fin >> N >> K >> M;
    while (Low < High) {
        ll Mid = Low + (High - Low + 1) / 2;
        if (IsValidX(N, K, M, Mid)) Low = Mid;
        else High = Mid - 1;
    }
    assert(Low == High);
    fout << Low << "\n";
    return 0;
}
