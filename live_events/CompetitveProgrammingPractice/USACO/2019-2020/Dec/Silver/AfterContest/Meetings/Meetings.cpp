#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

ofstream fout("meetings.out");
ifstream fin("meetings.in");

int main() {
    int N, L, TotalWeight = 0, ArrivedWeight = 0, T, Meetings = 0;
    vector<int> Weights, CurrentCows;
    vector<simps> ArrivalTime;
    vector<threesome> Cows;
    fin >> N >> L;
    for (int i = 0; i < N; i++) {
        int w, x, d;
        fin >> w >> x >> d;
        TotalWeight += w;
        Cows.push_back({x, {d, w}});    
    }
    sort(all(Cows));
    for (threesome t : Cows) {
        Weights.push_back(t.third);
        if (t.sec == 1) ArrivalTime.push_back({L - t.first, 1});
        else ArrivalTime.push_back({t.first, -1});
    }
    sort(all(ArrivalTime));
    while (ArrivedWeight * 2 < TotalWeight) {
        assert(ArrivalTime.size() > 0 and ArrivalTime.size() == Weights.size());
        T = ArrivalTime[0].first;
        while (ArrivalTime.size() > 0 and Weights.size() > 0 and ArrivalTime[0].first == T) {
            if (ArrivalTime[0].second == 1) {
                ArrivedWeight += Weights.back();
                Weights.pop_back();
            }
            else {
                ArrivedWeight += Weights[0];
                Weights.erase(Weights.begin());
            }
            ArrivalTime.erase(ArrivalTime.begin());
        }
    }
    for (threesome t : Cows) {
        if (t.sec == 1) CurrentCows.push_back(t.first);
        else {
            int x = t.first;
            while (CurrentCows.size() > 0 and x - CurrentCows[0] > 2 * T) CurrentCows.erase(CurrentCows.begin());
            Meetings += CurrentCows.size();
        }
    }
    fout << Meetings << "\n";
    return 0;
}
