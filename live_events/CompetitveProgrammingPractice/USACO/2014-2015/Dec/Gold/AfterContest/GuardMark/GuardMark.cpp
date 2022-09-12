#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second

int N, H;
ll Ans = -1;
vector<threesome> Cows;

int main() {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
    
    cin >> N >> H;
    Cows.resize(N);
    for (threesome& t : Cows) cin >> t.first >> t.sec >> t.third;

    vector<ll> Dp(1 << N, -1);

    for (int i = 0; i < N; i++) Dp[1 << i] = Cows[i].third;
    
    for (int i = 0; i < 1 << N; i++) {
        ll Height = 0;

        for (int j = 0; j < N; j++) {
            if ((i & (1 << j)) == 0) continue;

            Height += Cows[j].first;

            Dp[i] = max(min(Dp[i ^ (1 << j)] - Cows[j].sec, (ll) Cows[j].third), Dp[i]);
        }

        if (Height >= H) Ans = max(Dp[i], Ans);
    }

    cout << (Ans >= 0 ? to_string(Ans) : "Mark is too tall") << "\n";

    return 0;
}
