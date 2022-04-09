#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

ofstream fout("tracing.out");
ifstream fin("tracing.in");

bool SortEvents(const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}

bool SimInfect(const vector<vector<int> >& Events, const unordered_set<int>& FinSick, int StartInfected, int K) {
    unordered_set<int> Infected = {StartInfected};
    unordered_map<int, int> InfectedHooveShakes = {{StartInfected, 0}};
    if (StartInfected == 1 and K == 7)
        fout << "";
    for (vector<int> v : Events) {
        if (InfectedHooveShakes.count(v[1]) > 0 and InfectedHooveShakes[v[1]] < K) {
            if (Infected.count(v[2]) == 0) {
                Infected.insert(v[2]);
                InfectedHooveShakes[v[2]] = 0;
            }
            else InfectedHooveShakes[v[2]]++;
            InfectedHooveShakes[v[1]]++;
        }
        else if (InfectedHooveShakes.count(v[2]) > 0 and InfectedHooveShakes[v[2]] < K) {
            if (Infected.count(v[1]) == 0) {
                Infected.insert(v[1]);
                InfectedHooveShakes[v[1]] = 0;
            }
            else InfectedHooveShakes[v[1]]++;
            InfectedHooveShakes[v[2]]++;
        }
    }
    return Infected == FinSick;
}

int main() {
    int N, T, t, x, y, LowBound = 250, HighBound = 0, TotalPossible = 0;
    bool Works;
    string FinCond;
    unordered_set<int> FinSick;
    vector<vector<int> > Events;
    fin >> N >> T >> FinCond;
    for (int i = 0; i < N; i++) {
        if (FinCond[i] == '1') FinSick.insert(i + 1);
    }
    for (int i = 0; i < T; i++) {
        fin >> t >> x >> y;
        Events.push_back({t, x, y});
    }
    sort(Events.begin(), Events.end(), SortEvents);
    for (int i = 1; i <= N; i++) {
        Works = false;
        for (int K = 0; K <= 250; K++) {
            if (i == 2 and K == 1)
                fout << "";
            if (SimInfect(Events, FinSick, i, K)) {
                Works = true;
                if (K < LowBound) LowBound = K;
                if (K > HighBound) HighBound = K;
            }
        }
        if (Works) TotalPossible++;
    }
    fout << TotalPossible << " " << LowBound << " ";
    if (HighBound == 250) fout << "Infinity";
    else fout << HighBound << "\n";
    return 0;
}
