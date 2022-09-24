#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
string Seq;
vector<int> CharCount;
vector<vector<int> > PairCount;

void ReadInput() {
    int Prev = -1;
    vector<int> CharMap(26, -1);
    vector<bool> Exists(26);

    for (char c : Seq) Exists[c - 'a'] = true;

    for (int i = 0; i < 26; i++) {
        if (not Exists[i]) continue;

        CharMap[i] = N;
        N++;
    }

    CharCount.resize(N);
    PairCount.resize(N, vector<int>(N));

    for (char c : Seq) {
        int Mapped = CharMap[c - 'a'];

        assert(Mapped != -1);
        
        CharCount[Mapped]++;

        if (Prev != -1) PairCount[Prev][Mapped]++;

        Prev = Mapped;
    }
    
    return;
}

int main() {
    cin >> Seq;
    ReadInput();

    vector<vector<int> > Dp(1 << N, vector<int>(N, -1));

    for (int i = 1; i < (1 << N); i++) {
        for (int j = 0; j < N; j++) {
            if ((i & (1 << j)) == 0) continue;

            int Best = 1e9, Remove = 0;

            for (int k = 0; k < N; k++) {
                if (k == j or (i & (1 << k)) == 0) continue;

                Best = min(Dp[i ^ (1 << j)][k], Best);
                Remove += PairCount[k][j];
            }
            
            if (Best == 1e9) Dp[i][j] = CharCount[j];
            else Dp[i][j] = CharCount[j] + Best - Remove;
        }
    }
    
    int Ans = 1e9;

    for (int i : Dp.back()) Ans = min(i, Ans);

    assert(Ans != -1);

    cout << Ans << "\n";

    return 0;
}
