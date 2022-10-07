#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

double ValidTime(const double T, const int N, const vector<int>& Locs, const vector<int>& Times) {
    double Low = 0, High = 1e8;

    for (int i = 0; i < N; i++) {
        double CurLow = Locs[i] - (T - Times[i]), CurHigh = Locs[i] + (T - Times[i]);
        
        if (CurHigh < Low or CurLow > High) return -1;

        Low = max(CurLow, Low);
        High = min(CurHigh, High);
    }

    return Low;
}

double Subcase() {
    int N;
    double Low = 0, High = 2e8;
    cin >> N;
    vector<int> Locs(N), Times(N);
    for (int i = 0; i < N; i++) cin >> Locs[i];
    for (int i = 0; i < N; i++) {
        cin >> Times[i];
        Low = max((double) Times[i], Low);
    }

    while (Low < High) {
        double Mid = Low + (High - Low) / 2;

        if (ValidTime(Mid, N, Locs, Times) != -1) High = Mid;
        else Low = Mid;
        cout << Low << " " << High << "\n";
    }

    return ValidTime(Low, N, Locs, Times);
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) cout << Subcase() << "\n";

	return 0;
}
