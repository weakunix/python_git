#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("convention.out");
ifstream fin("convention.in");

bool IsPsblWait(const vector<int>& ArrivalTimes, int Wait, int M, int C) {
    int Prev, OnBus = C, BusesNeeded = 0;
    for (int i : ArrivalTimes) {
        if (OnBus == C or i - Prev > Wait) {
            BusesNeeded++;
            OnBus = 1;
            Prev = i;
        }
        else OnBus++;
            
    }
    return BusesNeeded <= M;
}

int main() {
    int N, M, C, Low = 0, High = 1e9, Ans = -1;
    fin >> N >> M >> C;
    vector<int> ArrivalTimes(N);
    for (int i = 0; i < N; i++) fin >> ArrivalTimes[i];
    sort(all(ArrivalTimes));
    while (Low <= High) {
        int Mid = Low + (High - Low + 1) / 2;
        if (IsPsblWait(ArrivalTimes, Mid, M, C)) {
            Ans = Mid;
            High = Mid - 1;
        }
        else Low = Mid + 1;
    }
    assert(Ans > -1);
    fout << Ans << "\n";
    return 0;
}
