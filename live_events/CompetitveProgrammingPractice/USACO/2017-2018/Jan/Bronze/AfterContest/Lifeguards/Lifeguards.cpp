/*
Test outputs

1:
7
*/

#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

ofstream fout("lifeguards.out");
ifstream fin("lifeguards.in");

int main() {

    //Vars
    int N, ShiftStart, ShiftEnd, TotalTimeCovered, CurTimeCovered, BestTimeCovered = 0;
    vector<vector<int> > Shifts;
    unordered_map<int, int> LgOnDuty;
    set<int> TimeCovered;

    //Temp vars
    vector<int> temp_vect_int;

    //Set vars
    for (int i = 0; i <= 1000; i++)
        LgOnDuty[i] = 0;

    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> ShiftStart >> ShiftEnd;
        Shifts.push_back({ShiftStart, ShiftEnd});
        for (int k = ShiftStart; k < ShiftEnd; k++) {
            LgOnDuty[k]++;
            TimeCovered.insert(k);
        }
    }
    TotalTimeCovered = TimeCovered.size();
    for (vector<int> v : Shifts) {
        CurTimeCovered = TotalTimeCovered;
        for (int i = v[0]; i < v[1]; i++) {
            if (LgOnDuty[i] == 1) {
                CurTimeCovered--;
            }
        }
        if (CurTimeCovered > BestTimeCovered)
            BestTimeCovered = CurTimeCovered;
    }
    fout << BestTimeCovered << "\n";
    return 0;
}
