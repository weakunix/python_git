#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

int N, GuessIdx = 0, HiloCount = 0;
vector<int> Guess, High, Low, To, From;

bool CmpTempNot(const int a, const int b) {
    return Guess[a] < Guess[b];
}

set<int, decltype(CmpTempNot)*> TempNot(CmpTempNot);

void MoveToLow(const int x) {
    int Idx = High.back();

    if (To[Idx] != -1 and Guess[To[Idx]] <= x) HiloCount--;
    assert(HiloCount >= 0);
    if (From[Idx] != -1 and Guess[From[Idx]] > x) HiloCount++;

    High.pop_back();

    while (not Low.empty() and Low.back() > Idx) {
        int Before = From[Low.back()], After = To[Low.back()];

        assert(HiloCount >= 0);

        Low.pop_back();

        if (Before != -1) {
            To[Before] = After;
            if (Guess[Before] > x) HiloCount--;
        }
        if (After != -1) From[After] = Before;

        if ((Before != -1 and After != -1) and (Guess[Before] > x and Guess[After] <= x)) HiloCount++;
    }

    Low.push_back(Idx);

    while (not TempNot.empty() and (High.empty() or Guess[*TempNot.begin()] < Guess[High.back()])) {
        int CurIdx = *TempNot.begin(), Before = -1, After = -1;
        auto LowIt = lower_bound(all(Low), CurIdx);

        TempNot.erase(TempNot.begin());

        if (not High.empty()) Before = High.back();

        if (LowIt != Low.end()) After = *LowIt;
        if (LowIt != Low.begin()) {
            LowIt--;
            Before = max(*LowIt, Before);
        }

        From[CurIdx] = Before;
        To[CurIdx] = After;
        if (Before != -1) To[Before] = CurIdx;
        if (After != -1) {
            From[After] = CurIdx;

            assert(Guess[After] <= x);
            HiloCount++;
        }

        High.push_back(CurIdx);
    }

    return;
}

int main() {
    freopen("2.in", "r", stdin);
    //freopen("test.in", "r", stdin);
    
    cin >> N;
    Guess.resize(N);
    To.resize(N, -1);
    From.resize(N, -1);
    for (int i = 0; i < N; i++) cin >> Guess[i];

    while (true) {
        assert(GuessIdx < N);

        if (High.empty()) {
            High.push_back(GuessIdx);
            GuessIdx++;
            continue;
        }

        assert(GuessIdx > 0);

        if (Guess[GuessIdx] < Guess[High.back()]) {
            To[High.back()] = GuessIdx;
            From[GuessIdx] = High.back();
            High.push_back(GuessIdx);
        }
        else TempNot.insert(GuessIdx);
        GuessIdx++;

        if (Guess[GuessIdx - 1] == 1) break;
    }

    cout << "0\n";

    for (int x = 1; x < N; x++) {
        assert(not High.empty());
        assert(Guess[High.back()] == x);

        MoveToLow(x);

        while (High.empty() or Guess[High.back()] != x + 1) {
            assert(GuessIdx < N);

            if (High.empty()) {
                if (not Low.empty()) {
                    To[Low.back()] = GuessIdx;
                    From[GuessIdx] = Low.back();
                }

                High.push_back(GuessIdx);
                GuessIdx++;
                continue;
            }
            
            assert(GuessIdx > 0);

            if (Guess[GuessIdx] < Guess[High.back()]) {
                int Before = High.back();
                if (not Low.empty()) Before = max(Low.back(), Before);
                To[Before] = GuessIdx;
                From[GuessIdx] = Before;
                High.push_back(GuessIdx);
            }
            else TempNot.insert(GuessIdx);
            GuessIdx++;
        }

        cout << HiloCount << "\n";
    }

    cout << "0\n";

    return 0;
}
