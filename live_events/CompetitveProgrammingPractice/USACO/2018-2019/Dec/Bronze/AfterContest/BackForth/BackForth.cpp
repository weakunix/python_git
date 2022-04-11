#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

#include <iostream>

using namespace std;

ofstream fout("backforth.out");
ifstream fin("backforth.in");

unordered_set<int> Outcomes(const unordered_map<int, int>& BarnStart, const unordered_map<int, int>& BarnEnd, int Day, int BarnStartMilk) {
    if (Day == 5) return {BarnStartMilk};
    unordered_set<int> Total;
    if (Day == 1)
        cout << "";
    for (auto it = BarnStart.begin(); it != BarnStart.end(); it++) {
        int i = it->first;
        unordered_map<int, int> TempBarnStart = BarnStart;
        unordered_map<int, int> TempBarnEnd = BarnEnd;
        TempBarnStart[i]--;
        if (TempBarnStart[i] == 0) TempBarnStart.erase(i);
        if (TempBarnEnd.count(i) > 0) TempBarnEnd[i]++;
        else TempBarnEnd[i] = 1;
        unordered_set<int> Some = Outcomes(TempBarnEnd, TempBarnStart, Day + 1, BarnStartMilk + pow(-1, Day) * i);
        for (int k : Some) Total.insert(k);
    }
    return Total;
}

int main() {
    int BucketSize;
    unordered_map<int, int> Barn1, Barn2;
    for (int i = 0; i < 10; i++) {
        fin >> BucketSize;
        if (Barn1.count(BucketSize) > 0) Barn1[BucketSize]++;
        else Barn1[BucketSize] = 1;
    }
    for (int i = 0; i < 10; i++) {
        fin >> BucketSize;
        if (Barn2.count(BucketSize) > 0) Barn2[BucketSize]++;
        else Barn2[BucketSize] = 1;
    }
    fout << Outcomes(Barn1, Barn2, 1, 1000).size() << "\n";
    return 0;
}
