#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

void GetBestCases(const vector<int>& Carrots, vector<int>& BestCases, const int N, const int K) {
    int First = 0, Second = 0, Count = 0;
    while (First < N) {
        if (Second < N and Carrots[Second] - Carrots[First] <= K) {
            Count++;
            Second++;
        }
        else {
            BestCases.push_back(Count);
            First++;
            Count--;
        }
    }
    return;
}

int main() {
    int N, K, Best = 0;
    vector<int> BestCases, BestCasesCopy, CarrotCopy, BestSecondCases = {0};
    cin >> N >> K;
    vector<int> Carrots(N);
    for (int i = 0; i < N; i++) cin >> Carrots[i];
    sort(all(Carrots));
    GetBestCases(Carrots, BestCases, N, K);
    CarrotCopy = Carrots;
    BestCasesCopy = BestCases;
    reverse(all(Carrots));
    for (int i : Carrots) {
        int CurBest = BestSecondCases.back();
        while (CarrotCopy.size() > 0 and CarrotCopy.back() - i > K) {
            CurBest = max(BestCasesCopy.back(), CurBest);
            CarrotCopy.pop_back();
            BestCasesCopy.pop_back();
        }
        BestSecondCases.push_back(CurBest);
    }
    reverse(all(BestSecondCases));
    for (int i = 0; i < N; i++) Best = max(BestCases[i] + BestSecondCases[i], Best);
    cout << Best << "\n";
    return 0;
}
