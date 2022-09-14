#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

int N;
vector<int> Guess, Idx, CorHigh;
vector<bool> IsHigh;
vector<vector<int> > BecomeHigh;
vector<unordered_set<int> > CorLow;

void SetHighs() {
    int CurLow = 1e9;

    for (int i : Guess) {
        BecomeHigh[((i < CurLow) ? 0 : CurLow)].push_back(Idx[i]);
        CurLow = min(i, CurLow);
    }

    return;
}

void SetCorHighs() {
    vector<int> Stck;
    
    for (int i = 0; i < N; i++) {
        while (not Stck.empty() and Guess[i] < Guess[Stck.back()]) Stck.pop_back();
        CorHigh[i] = ((Stck.empty()) ? -1 : Stck.back());
        Stck.push_back(i);
    }

    return;
}

int main() {
    cin >> N;
    Guess.resize(N);
    Idx.resize(N);
    CorHigh.resize(N);
    IsHigh.resize(N);
    BecomeHigh.resize(N);
    CorLow.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> Guess[i];
        Idx[Guess[i]] = i;
    }

    SetHighs();
    SetCorHighs();

    int HiloCount = 0;
    vector<int> LowStck;

    cout << "0\n";

    for (int i = 1; i <= N; i++) {
        int CurIdx = Idx[i];

        IsHigh[CurIdx] = false;
        if (not CorLow[CurIdx].empty()) HiloCount--;

        while (not LowStck.empty() and CurIdx < LowStck.back()) {
            int CurHigh = CorHigh[LowStck.back()];
            CorLow[CurHigh].erase(LowStck.back());
            if (CorLow[CurHigh].empty() and IsHigh[CurHigh]) HiloCount--;
            LowStck.pop_back();
        }

        LowStck.push_back(CurIdx);
        if (CorHigh[CurIdx] != -1) {
            if (CorLow[CorHigh[CurIdx]].empty() and IsHigh[CorHigh[CurIdx]]) HiloCount++;
            CorLow[CorHigh[CurIdx]].insert(CurIdx);
        }

        for (int j : BecomeHigh[i]) {
            IsHigh[j] = true;
            if (not CorLow[j].empty()) HiloCount++;
        }

        cout << HiloCount << "\n";
    }

    return 0;
}
