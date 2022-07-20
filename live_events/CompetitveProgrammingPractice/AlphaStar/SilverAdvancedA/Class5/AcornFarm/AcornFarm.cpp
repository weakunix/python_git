#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> pipii;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

int main() {
    int N, A, Changes = 0;
    vector<pipii> Log;
    map<int, int> CowsToMeasurement, MeasurementsToCows;
    cin >> N >> A;
    int BestProd = A;
    MeasurementsToCows[A] = 1e6;
    for (int i = 0; i < N; i++) {
        int Day, Id, Change;
        cin >> Day >> Id >> Change;
        CowsToMeasurement[Id] = A;
        Log.push_back({Day, {Id, Change}});
    }
    sort(all(Log));
    for (const pipii& p : Log) {
        int Id = p.sec, Change = p.third, Prod = CowsToMeasurement[Id], NewBestProd;
        bool WasBest = (Prod == BestProd);
        MeasurementsToCows[Prod]--;
        if (MeasurementsToCows[Prod] == 0) MeasurementsToCows.erase(Prod);
        CowsToMeasurement[Id] += Change;
        Prod += Change;
        if (MeasurementsToCows.count(Prod) == 0) MeasurementsToCows[Prod] = 1;
        else MeasurementsToCows[Prod]++;
        NewBestProd = MeasurementsToCows.rbegin()->first;
        if (Prod == BestProd) Changes++;
        else if (Prod < BestProd) {
            if (WasBest) {
                if (Prod != NewBestProd or MeasurementsToCows[NewBestProd] > 1) Changes++;
            }
        }
        else {
            if (WasBest) {
                if (MeasurementsToCows.count(Prod - Change) > 0) Changes++;
            }
            else Changes++;
        }
        BestProd = NewBestProd;
    }
    cout << Changes << "\n";
    return 0;
}
