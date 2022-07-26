#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int N, M, PrimeCount, Count = 2, Ans = 0;
    vector<int> Primes;
    vector<vector<ll> > Dp;
    cin >> N >> M;
    for (int i = 2; i <= N; i++) {
        bool Works = true;
        for (int j : Primes) {
            if (j > sqrt(i)) break;
            if (i % j == 0) {
                Works = false;
                break;
            }
        }
        if (Works) Primes.push_back(i);
    }
    PrimeCount = Primes.size();
    Dp.resize(PrimeCount);
    for (int i = 0; i < PrimeCount; i++) Dp[i].resize(N + 1);
    Dp[0][0] = 1;
    while (Count <= N) {
        Dp[0][Count] = Count;
        Count *= 2;
    }
    for (int p = 0; p < PrimeCount - 1; p++) {
        vector<int> CurPows = {1};
        while (CurPows.back() < N) CurPows.push_back(CurPows.back() * Primes[p + 1]);
        for (int n = 0; n <= N; n++) {
            while (CurPows.back() > N - n and CurPows.back() != 1) CurPows.pop_back();
            for (int i : CurPows) {
                if (i == 1) Dp[p + 1][n] = (Dp[p + 1][n] + Dp[p][n]) % M;
                else Dp[p + 1][n + i] = (Dp[p + 1][n + i] + Dp[p][n] * i) % M;
            }
        }
    }
    for (int i = 0; i <= N; i++) Ans = (Ans + Dp[PrimeCount - 1][i]) % M;
    cout << Ans << "\n";
    return 0;
}
