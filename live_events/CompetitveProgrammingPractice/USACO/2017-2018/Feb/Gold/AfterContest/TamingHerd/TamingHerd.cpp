#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int MinLogChangeDp(const vector<int>& Log, const int N, const int K) {
    int Res = 1000;
    vector<int> DpRow(N, 1000);
    vector<vector<int> > Dp(K, DpRow);
    Dp[0][0] = (Log[0] != 0);
    for (int k = 1; k < K; k++) {
        for (int j = 0; j < N; j++) {
            int NewChanges = 0;
            for (int n = 1; j + n < N; n++) {
                Dp[k][j + n] = min(Dp[k - 1][j] + NewChanges + (Log[j + n] != 0), Dp[k][j + n]);
                if (n > 0 and Log[j + n] != n) NewChanges++;
            }
        }
    }
    for (int n = 0; n < N; n++) {
        int Cur = Dp[K - 1][n];
        for (int i = 1; n + i < N; i++) {
            if (Log[n + i] != i) Cur++;
        }
        Res = min(Cur, Res);
    }
    return Res;
}

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    int N;
    cin >> N;
    vector<int> Log(N);
    for (int i = 0; i < N; i++) cin >> Log[i];
    for (int i = 1; i <= N; i++) cout << MinLogChangeDp(Log, N, i) << "\n";
    return 0;
}
