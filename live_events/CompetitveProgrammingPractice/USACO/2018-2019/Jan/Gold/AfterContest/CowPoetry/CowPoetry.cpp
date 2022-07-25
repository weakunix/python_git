#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

const int ModVal = 1e9 + 7;

int Pow(const int n, int e) {
    assert(e > 0);
    e++;
    int Cur = 1, Count = 0, Res = 1;
    vector<int> PowOfTwo = {n};
    while (Cur * 2 <= e) {
        Cur *= 2;
        Count++;
        PowOfTwo.push_back(((ll) PowOfTwo.back() * PowOfTwo.back()) % ModVal);
    }
    while (Count >= 0) {
        if (e > Cur) {
            Res = ((ll) Res * PowOfTwo[Count]) % ModVal;
            e -= Cur;
        }
        Cur /= 2;
        Count--;
    }
    return Res;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    int N, M, K;
    ll Ans = 1;
    cin >> N >> M >> K;
    vector<int> RhymeScheme(26), Dp(K + 1), Classes(N);
    vector<simps> Words;
    for (int i = 0; i < N; i++) {
        int s, c;
        cin >> s >> c;
        c--;
        Words.push_back({s, c});
    }
    for (int i = 0; i < M; i++) {
        char e;
        cin >> e;
        RhymeScheme[e - 'A']++;
    }
    Dp[0] = 1;
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j < N; j++) {
            int s = Words[j].first;
            if (i - s >= 0) Dp[i] = (Dp[i] + Dp[i - s]) % ModVal;
        }
    }
    for (const simps& s : Words) Classes[s.second] = (Classes[s.second] + Dp[K - s.first]) % ModVal;
    for (int i : RhymeScheme) {
        if (i > 0) {
            int Cur = 0;
            for (int j : Classes) {
                Cur = (Cur + Pow(j, i)) % ModVal;
            }
            Ans = (Ans * Cur) % ModVal;
        }
    }
    cout << Ans << "\n";
    return 0;
}
