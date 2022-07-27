#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

void InputPath(vector<simps>& Points, const int Times) {
    for (int i = 0; i < Times; i++) {
        char c;
        cin >> c;
        if (c == 'N') Points.push_back({Points.back().first, Points.back().second + 1});
        else if (c == 'S') Points.push_back({Points.back().first, Points.back().second - 1});
        else if (c == 'E') Points.push_back({Points.back().first + 1, Points.back().second});
        else Points.push_back({Points.back().first - 1, Points.back().second});
    }
    return;
}

int GetDist(const simps& a, const simps& b) {
    int x = a.first - b.first, y = a.second - b.second;
    return x * x + y * y;
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    int N, M;
    vector<simps> Fj(1), Bessie(1);
    cin >> N >> M;
    vector<vector<int> > Dp(N + 1);
    for (int i = 0; i <= N; i++) Dp[i].resize(M + 1);
    
    cin >> Fj[0].first >> Fj[0].second >> Bessie[0].first >> Bessie[0].second;
    InputPath(Fj, N);
    InputPath(Bessie, M);
    for (int f = 0; f <= N; f++) {
        for (int b = 0; b <= M; b++) {
            if (f == 0 and b == 0) continue;
            Dp[f][b] = 2e9;
            if (f > 0 and b > 0) Dp[f][b] = min(Dp[f - 1][b - 1], Dp[f][b]);
            if (f > 0) Dp[f][b] = min(Dp[f - 1][b], Dp[f][b]);
            if (b > 0) Dp[f][b] = min(Dp[f][b - 1], Dp[f][b]);
            Dp[f][b] += GetDist(Fj[f], Bessie[b]);
        }
    }
    cout << Dp[N][M] << "\n";
    return 0;
}
