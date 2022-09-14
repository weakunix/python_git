#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
vector<int> Guess, Idx, PrevHigh;
vector<bool> IsHigh;
vector<vector<int> > BecomeHigh;
vector<unordered_set<int> > CorLow;

void SetPrevHigh() {
    set<int> PrevNums;

    for (int i = 0; i < N; i++) {
        PrevNums.insert(Guess[i]);
        
        auto it = PrevNums.upper_bound(Guess[i]);
        
        PrevHigh[i] = ((it == PrevNums.end()) ? -1 : Idx[*it - 1]);
    }

    return;
}

void SetBecomeHigh() {
    set<int> PrevNums;

    for (int i = 0; i < N; i++) {
        PrevNums.insert(Guess[i]);
        
        auto it = PrevNums.find(Guess[i]);

        if (it == PrevNums.begin()) IsHigh[i] = true;
        else {
            it--;
            BecomeHigh[*it].push_back(i);
        }
    }

    return;
}

int main() {
    cin >> N;
    Guess.resize(N);
    Idx.resize(N);
    PrevHigh.resize(N);
    BecomeHigh.resize(N);
    IsHigh.resize(N);
    CorLow.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> Guess[i];
        Idx[Guess[i] - 1] = i;
    }

    SetPrevHigh();
    SetBecomeHigh();

    int HiloCount = 0;
    vector<int> LowStck;

    cout << "0\n";

    for (int i = 1; i < N; i++) {
        int CurIdx = Idx[i - 1];

        if (not CorLow[CurIdx].empty()) HiloCount--;
        IsHigh[CurIdx] = false;

        while (not LowStck.empty() and LowStck.back() > CurIdx) {
            CorLow[PrevHigh[LowStck.back()]].erase(LowStck.back());
            if (CorLow[PrevHigh[LowStck.back()]].empty() and IsHigh[PrevHigh[LowStck.back()]]) HiloCount--;
            LowStck.pop_back();
        }
        
        if (PrevHigh[CurIdx] != -1) {
            LowStck.push_back(CurIdx);
            if (CorLow[PrevHigh[CurIdx]].empty() and IsHigh[PrevHigh[CurIdx]]) HiloCount++;
            CorLow[PrevHigh[CurIdx]].insert(CurIdx);
        }
        
        for (int j : BecomeHigh[i]) {
            IsHigh[j] = true;
            HiloCount += (not CorLow[j].empty());
        }

        cout << HiloCount << "\n";

    }

    cout << "0\n";

    return 0;
}
