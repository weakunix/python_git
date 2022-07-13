#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    int N, K;
    ll Ans = 1e10;
    cin >> N >> K;
    vector<int> Cows(N);
    const vector<ll> Row(N, 1e10);
    for (int i = 0; i < N; i++) cin >> Cows[i];
    for (int i = 0; i < N; i++) {
        ll CurAddVal = 0, CurVal = 0;
        vector<vector<ll> > Dp(K, Row);
        Dp[0][0] = 0;
        for (int k = 1; k < K; k++) {
            for (int j = 0; j < N; j++) {
                ll NewVals = 0;
                for (int n = 0; j + n < N; n++) {
                    Dp[k][j + n] = min(Dp[k - 1][j] + NewVals, Dp[k][j + n]);
                    if (Dp[k][j + n] < 0)
                        cout << "blah\n";
                    NewVals += (ll) n * Cows[j + n];
                }
            }
        }
        for (int n = N - 1; n >= 0; n--) {
            Ans = min(Dp[K - 1][n] + CurVal, Ans);
            CurAddVal += Cows[n];
            CurVal += CurAddVal;
        }
        rotate(Cows.begin(), Cows.begin() + 1, Cows.end());
    }
    cout << Ans << "\n";
    return 0;
}
