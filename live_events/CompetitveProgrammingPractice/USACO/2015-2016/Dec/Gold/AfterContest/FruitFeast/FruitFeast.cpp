#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    int T, A, B;
    cin >> T >> A >> B;
    vector<bool> Dp(T + 1);
    Dp[0] = true;
    for (int i = 1; i <= T; i++) {
        if ((i - A >= 0 and Dp[i - A]) or (i - B >= 0 and Dp[i - B])) Dp[i] = true;
    }
    for (int i = 1; i <= T; i++) {
        if (Dp[i]) Dp[i / 2] = true;
    }
    for (int i = 1; i <= T; i++) {
        if ((i - A >= 0 and Dp[i - A]) or (i - B >= 0 and Dp[i - B])) Dp[i] = true;
    }
    for (int i = T; i >= 0; i--) {
        if (Dp[i]) {
            cout << i << "\n";
            return 0;
        }
    }
    return 1;
}
