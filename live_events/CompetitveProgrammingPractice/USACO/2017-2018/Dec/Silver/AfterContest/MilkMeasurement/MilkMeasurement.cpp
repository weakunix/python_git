#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()

ofstream fout("measurement.out");
ifstream fin("measurement.in");

int main() {
    int N, G, CurMax, Changes = 0;
    vector<threesome> MilkLogs;
    map<int, int> CowMilkProduction, CowCountPerMilk;
    fin >> N >> G;
    CurMax = G;
    CowCountPerMilk[G] = 1e9;
    for (int i = 0; i < N; i++) {
        int Day, ID, MilkChange;
        fin >> Day >> ID >> MilkChange;
        CowMilkProduction[ID] = G;
        MilkLogs.push_back({Day, {ID, MilkChange}});
    }
    sort(all(MilkLogs));
    for (const threesome& t : MilkLogs) {
        int ID = t.sec, MilkChange = t.third, InitialVal = CowMilkProduction[ID], CurVal;
        CowMilkProduction[ID] += MilkChange;
        CurVal = CowMilkProduction[ID];
        assert(InitialVal != CurVal);
        assert(InitialVal <= CurMax);
        if (CowCountPerMilk[InitialVal] == 1) CowCountPerMilk.erase(InitialVal);
        else CowCountPerMilk[InitialVal]--;
        if (CowCountPerMilk.count(CurVal) == 0) CowCountPerMilk[CurVal] = 1;
        else CowCountPerMilk[CurVal]++;
        if (CurVal == CurMax) Changes++;
        else if (CurVal > CurMax) {
            if (InitialVal != CurMax or CowCountPerMilk.count(InitialVal) > 0) Changes++;
            CurMax = CurVal;
        }
        else if (InitialVal == CurMax) {
            assert(CurVal < InitialVal);
            auto LastElem = CowCountPerMilk.end();
            LastElem--;
            if (LastElem->first != CurVal or LastElem->second > 1) Changes++;
            CurMax = LastElem->first;
        }
    }
    fout << Changes << "\n";
    return 0;
}
