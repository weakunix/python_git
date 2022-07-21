#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);
    const int ModVal = 1e9 + 7;
    ll N, M, K, Total = 1;
    vector<ll> Dp = {1};
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) Total = (Total * M) % ModVal;
    for (int i = 1; i <= N; i++) {
        Dp.push_back((M * Dp[i - 1]) % ModVal);
        if (i >= K) Dp[i] = (Dp[i] + ModVal - (M * Dp[i - K]) % ModVal) % ModVal;
        if (i > K) Dp[i] = (Dp[i] + Dp[i - K]) % ModVal;
    }
    cout << (Total + ModVal - Dp[N]) % ModVal << "\n";
    return 0;
}
