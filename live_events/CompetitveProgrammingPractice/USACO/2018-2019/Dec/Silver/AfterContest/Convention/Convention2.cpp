#include <fstream>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

ofstream fout("convention.out");
ifstream fin("convention.in");

int GetMaxWait(int Wait, const set<int>& ArrivalTimes, int C) {
    int Prev = *ArrivalTimes.begin(), MaxWait = 0;
    for (int i : ArrivalTimes) {
        if (i - Prev > Wait) {
            C--;
            if (C == 0) return -1;
            Prev = i;
        }
        else MaxWait = max(i - Prev, MaxWait);
    }
    assert(C > 0);
    return MaxWait;
}

int main() {
    int N, M, C, Low = 0, High = 1e9, MinWait = -1;
    fin >> N >> M >> C;
    set<int> ArrivalTimes;
    for (int i = 0; i < N; i++) {
        int Time;
        fin >> Time;
        ArrivalTimes.insert(Time);
    }
    while (Low <= High) {
        int Mid = Low + (High - Low + 1) / 2, CurMaxWait = GetMaxWait(Mid, ArrivalTimes, C);
        if (CurMaxWait > -1) {
            if (MinWait == -1) MinWait = CurMaxWait;
            else MinWait = min(CurMaxWait, MinWait);
            High = Mid - 1;
        }
        else Low = Mid + 1;
    }
    assert(MinWait > -1);
    fout << MinWait << "\n";
    return 0;
}
