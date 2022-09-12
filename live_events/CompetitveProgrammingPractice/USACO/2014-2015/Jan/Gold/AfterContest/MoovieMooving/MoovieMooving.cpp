#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, vector<int> > magnet;

#define all(v) v.begin(), v.end()

int N, L, Ans = 1e9;
vector<magnet> Movies;

int FindMovieEnd(const int End, const int Idx) {
    if (Movies[Idx].second[0] > End) return -1;

    auto it = upper_bound(all(Movies[Idx].second), End);
    it--;
    
    return max(*it + Movies[Idx].first, End);
}

int main() {
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);

    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        int D, C;

        cin >> D >> C;

        Movies.push_back({D, vector<int>(C)});

        for (int j = 0; j < C; j++) cin >> Movies.back().second[j];
    }

    vector<int> Dp(1 << N);

    for (int i = 0; i < N; i++) {
        if (Movies[i].second[0] == 0) Dp[1 << i] = Movies[i].first;
    }

    for (int i = 0; i < (1 << N); i++) {
        int MovieCount = 0;

        for (int j = 0; j < N; j++) {
            if ((i & (1 << j)) == 0) continue;
            
            MovieCount++;

            Dp[i] = max(FindMovieEnd(Dp[i ^ (1 << j)], j), Dp[i]);
        }

        if (Dp[i] >= L) Ans = min(MovieCount, Ans);
    }

    cout << ((Ans != 1e9) ? Ans : -1) << "\n";

    return 0;
}
