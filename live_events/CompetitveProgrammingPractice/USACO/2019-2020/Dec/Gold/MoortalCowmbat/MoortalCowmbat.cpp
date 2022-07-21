#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    int N, M, K, Ans = 1e9;
    vector<int> CurSeq = {0};
    cin >> N >> M >> K;
    vector<vector<int> > ChangeMatrix(M), Pfx(M), Dp(M);
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        CurSeq.push_back(c - 'a');
    }
    for (int y = 0; y < M; y++) {
        for (int x = 0; x < M; x++) {
            int n;
            cin >> n;
            ChangeMatrix[y].push_back(n);
        }
    }

    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) ChangeMatrix[i][j] = min(ChangeMatrix[i][k] + ChangeMatrix[k][j], ChangeMatrix[i][j]);
        }
    }

    for (int m = 0; m < M; m++) {
        Pfx[m].push_back(0);
        for (int n = 1; n <= N; n++) Pfx[m].push_back(Pfx[m].back() + ChangeMatrix[CurSeq[n]][m]);
    }

    for (int m = 0; m < M; m++) Dp[m].push_back(0);
    for (int n = 1; n <= N; n++) {
        for (int m = 0; m < M; m++) {
            Dp[m].push_back(1e9);
            if (n - K < 0) continue;
            Dp[m][n] = min(Dp[m][n - 1] + ChangeMatrix[CurSeq[n]][m], Dp[m][n]);
            for (int i = 0; i < M; i++) Dp[m][n] = min(Dp[i][n - K] + Pfx[m][n] - Pfx[m][n - K], Dp[m][n]);
        }
    }

    for (int m = 0; m < M; m++) Ans = min(Dp[m][N], Ans);
    cout << Ans << "\n";
    return 0;
}
