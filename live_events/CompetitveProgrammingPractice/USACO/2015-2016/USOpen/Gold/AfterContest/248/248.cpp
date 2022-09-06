#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N, Ans = 0;
vector<int> Nums;

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);

    cin >> N;
    Nums.resize(N);
    for (int i = 0; i < N; i++) cin >> Nums[i];

    vector<vector<int> > Dp(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++) {
        Dp[i][i] = Nums[i];
        Ans = max(Nums[i], Ans);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N - i; j++) {
            for (int k = j; k < j + i; k++) {
                if (Dp[j][k] != -1 and Dp[j][k] == Dp[k + 1][j + i]) {
                    Dp[j][j + i] = Dp[j][k] + 1;
                    Ans = max(Dp[j][j + i], Ans);
                }
            }
        }
    }

    cout << Ans << "\n";

    return 0;
}
