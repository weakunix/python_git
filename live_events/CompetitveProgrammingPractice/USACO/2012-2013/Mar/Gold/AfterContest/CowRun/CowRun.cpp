#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int N;
vector<int> Pos = {0}, Neg = {0};

int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int Cow;
        cin >> Cow;
        if (Cow > 0) Pos.push_back(Cow);
        else Neg.push_back(Cow);
    }

    sort(all(Pos));
    sort(rall(Neg));

    int PosCount = Pos.size(), NegCount = Neg.size();
    vector<vector<ll> > DpPos(PosCount, vector<ll>(NegCount, 1e11)), DpNeg(PosCount, vector<ll>(NegCount, 1e11));

    DpPos[0][0] = 0;
    DpNeg[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        int NegIdx = 0, PosIdx = i, CowCount = N + 1 - i;
        
        if (PosIdx >= PosCount) {
            NegIdx = PosIdx - PosCount + 1;
            PosIdx = PosCount - 1;

            assert(NegIdx < NegCount);
        }

        while (PosIdx >= 0 and NegIdx < NegCount) {
            if (PosIdx > 0) {
                DpPos[PosIdx][NegIdx] = min(DpPos[PosIdx - 1][NegIdx] + abs(Pos[PosIdx - 1] - Pos[PosIdx]) * CowCount, DpPos[PosIdx][NegIdx]);
                DpPos[PosIdx][NegIdx] = min(DpNeg[PosIdx - 1][NegIdx] + abs(Neg[NegIdx] - Pos[PosIdx]) * CowCount, DpPos[PosIdx][NegIdx]);
            }
            if (NegIdx > 0) {
                DpNeg[PosIdx][NegIdx] = min(DpNeg[PosIdx][NegIdx - 1] + abs(Neg[NegIdx - 1] - Neg[NegIdx]) * CowCount, DpNeg[PosIdx][NegIdx]);
                DpNeg[PosIdx][NegIdx] = min(DpPos[PosIdx][NegIdx - 1] + abs(Pos[PosIdx] - Neg[NegIdx]) * CowCount, DpNeg[PosIdx][NegIdx]);
            }

            PosIdx--;
            NegIdx++;
        }
    }

    cout << min(DpPos[PosCount - 1][NegCount - 1], DpNeg[PosCount - 1][NegCount - 1]) << "\n";

    return 0;
}
