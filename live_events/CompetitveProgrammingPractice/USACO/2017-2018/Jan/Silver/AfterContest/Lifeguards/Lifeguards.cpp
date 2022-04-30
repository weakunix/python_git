#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

ofstream fout("lifeguards.out");
ifstream fin("lifeguards.in");

int main() {
    int N, Already = 0, Best = 0;
    vector<int> OnShift, ShiftNums, LoneShifts;
    vector<pair<int, int> > Shifts;
    set<int> SpecTimesSet;
    unordered_map<int, int> CompressMap;
    fin >> N;
    for (int i = 0; i < N; i++) {
        int a, b;
        fin >> a >> b;
        SpecTimesSet.insert(a);
        SpecTimesSet.insert(b);
        Shifts.push_back({a, b});
    }
    vector<int> SpecTimes(all(SpecTimesSet));
    for (int i = 0; i < SpecTimes.size(); i++) {
        CompressMap[SpecTimes[i]] = i;
        OnShift.push_back(0);
        if (i == SpecTimes.size() - 1) ShiftNums.push_back(1);
        else ShiftNums.push_back(SpecTimes[i + 1] - SpecTimes[i]);
    }
    for (pair<int, int>& p : Shifts) {
        int a = CompressMap[p.first], b = CompressMap[p.second];
        p.first = a;
        p.second = b;
        OnShift[a]++;
        OnShift[b]--;
    }
    for (int i = 0; i < OnShift.size(); i++) {
        if (i > 0) {
            OnShift[i] += OnShift[i - 1];
            LoneShifts.push_back(LoneShifts.back());
        }
        else LoneShifts.push_back(0);
        if (OnShift[i] > 0) {
            Already += ShiftNums[i];
            if (OnShift[i] == 1) LoneShifts[i] += ShiftNums[i];
        }
    }
    for (pair<int, int> p : Shifts) {
        int a = p.first, b = p.second;
        if (a == 0) Best = max(Already - LoneShifts[b - 1], Best);
        else Best = max(Already - (LoneShifts[b - 1] - LoneShifts[a - 1]), Best);
    }
    fout << Best << "\n";
    return 0;
}
