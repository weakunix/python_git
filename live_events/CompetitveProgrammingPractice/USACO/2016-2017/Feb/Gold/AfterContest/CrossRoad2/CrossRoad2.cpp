#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    
    int N;
    cin >> N;
    vector<int> First(N), Second(N);
    vector<vector<int> > Dp(N + 1);
    for (int i = 0; i <= N; i++) Dp[i].resize(N + 1);
    
    for (int i = 0; i < N; i++) cin >> First[i];
    for (int i = 0; i < N; i++) cin >> Second[i];
    
    for (int f = 1; f <= N; f++) {
        for (int s = 1; s <= N; s++) {
            int Count = s - 1;
            Dp[f][s] = Dp[f - 1][s];
            while (Count >= 0) {
                if (abs(First[f - 1] - Second[Count]) <= 4) {
                    Dp[f][s] = max(Dp[f - 1][Count] + 1, Dp[f][s]);
                    break;
                }
                Count--;
            }
        }
    }
    
    cout << Dp[N][N] << "\n";
    return 0;
}
