#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

double ValidTime(const ll T, const int N, const vector<ll>& Locs, const vector<ll>& Times) {
    ll Low = 0, High = 1e15;

    for (int i = 0; i < N; i++) {
        ll CurLow = Locs[i] - (T - Times[i]), CurHigh = Locs[i] + (T - Times[i]);
        
        if (CurHigh < Low or CurLow > High) return -1;

        Low = max(CurLow, Low);
        High = min(CurHigh, High);
    }

    return Low;
}

void Subcase() {
    int N;
    ll Low = 0, High = 2e15;
    cin >> N;
    vector<ll> Locs(N), Times(N);
    for (int i = 0; i < N; i++) {
        cin >> Locs[i];
        Locs[i] *= 1e7;
    }
    for (int i = 0; i < N; i++) {
        cin >> Times[i];
        Times[i] *= 1e7;
        Low = max(Times[i], Low);
    }

    while (Low < High) {
        ll Mid = Low + (High - Low) / 2;

        if (ValidTime(Mid, N, Locs, Times) != -1) High = Mid;
        else Low = Mid + 1;
    }

    //double Res = ValidTime(Low, N, Locs, Times) / 1e7;
    string Res = to_string(ValidTime(Low, N, Locs, Times) / 1e7);

    cout << Res << "\n";
    
    return;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) Subcase();

	return 0;
}
