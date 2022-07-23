#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ToInt(const char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return -1;
}

int main() {
    const int ModVal = 1e9 + 7;
    int N, Ans = 0;
    string S;
    cin >> S;
    N = S.size();
    vector<vector<vector<vector<int> > > > Dp;
    for (int i = 0; i < N; i++) {
        Dp.push_back({});
        for (int j = 0; j < 4; j++) {
            Dp[i].push_back({});
            for (int k = 0; k < 4; k++) {
                Dp[i][j].push_back({});
                for (int l = 0; l < 4; l++) Dp[i][j][k].push_back(0);
            }
        }
    }
    for (int i = 0; i < 1; i++) {
        int Cur = ToInt(S[i]);
        for (int j = 0; j < 4; j++) {
            if (Cur >= 0 and Cur != j) continue;
            for (int l = 0; l < 4; l++) Dp[0][j][j][l] = 1;
        }
    }
    for (int i = 1; i < N; i++) {
        int Cur = ToInt(S[i]);
        for (int j = 0; j < 4; j++) {
            if (Cur >= 0 and Cur != j) continue;
            for (int l = 0; l < 4; l++) {
                for (int a = 0; a < 4; a++) Dp[i][j][j][l] = (Dp[i][j][j][l] + Dp[i - 1][a][l][a]) % ModVal;
            }
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    for (int a = 0; a < 4; a++) {
                        if (a != j) Dp[i][j][k][l] = (Dp[i][j][k][l] + Dp[i - 1][a][k][l]) % ModVal;
                    }
                }
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) Ans = (Ans + Dp[N - 1][j][k][j]) % ModVal;
    }
    cout << Ans << "\n";
    return 0;
}
