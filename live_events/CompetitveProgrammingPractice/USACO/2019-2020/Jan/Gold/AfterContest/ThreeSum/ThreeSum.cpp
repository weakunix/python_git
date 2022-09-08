#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

const int Mil = 1e6;
int N, Q;
vector<int> A;

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);

    cin >> N >> Q;
    A.resize(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    vector<int> NumCount(2 * Mil + 1);
    vector<vector<ll> > Dp(N, vector<ll>(N));
    
    for (int i = 0; i < N - 2; i++) {
        NumCount[Mil + A[i + 1]]++;

        for (int j = i + 2; j < N; j++) {
            int Cur = Mil - (A[i] + A[j]);

            if (Cur >= 0 and Cur <= 2 * Mil) Dp[i][j] = NumCount[Cur];

            NumCount[Mil + A[j]]++;
        }

        for (int j = i + 1; j < N; j++) NumCount[Mil + A[j]]--;
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j < N; j++) Dp[i][j] += Dp[i + 1][j] + Dp[i][j - 1] - Dp[i + 1][j - 1];
    }

    for (int i = 0; i < Q; i++) {
        int a, b;
        cin >> a >> b;
        cout << Dp[a - 1][b - 1] << "\n";
    }

    return 0;
}
