#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    int N, K;
    vector<int> Dp = {0};
    cin >> N >> K;
    vector<int> Cows(N);
    for (int i = 0; i < N; i++) cin >> Cows[i];
    for (int i = 0; i < N; i++) {
        int MaxVal = 0;
        Dp.push_back(0);
        for (int j = 0; j < K; j++) {
            if (i - j < 0) break;
            MaxVal = max(Cows[i - j], MaxVal);
            Dp.back() = max((j + 1) * MaxVal + Dp[i - j], Dp.back());
        }
    }
    cout << Dp.back() << "\n";
    return 0;
}
