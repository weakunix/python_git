#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
vector<int> Painting;

int main() {
    cin >> N;
    Painting.resize(N);
    for (int i = 0; i < N; i++) cin >> Painting[i];

    vector<vector<int> > Dp(N, vector<int>(N));

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N - i; j++) {
            if (Painting[j] == Painting[j + i]) Dp[j][j + i] = Dp[j + 1][j + i - 1] + 1;

            for (int k = 0; k <= i; k++) Dp[j][j + i] = max(Dp[j][j + k] + Dp[j + k][j + i], Dp[j][j + i]);
        }
    }

    cout << N - Dp[0][N - 1] << "\n";

    return 0;
}
