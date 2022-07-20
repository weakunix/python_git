#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef pair<string, bool> psb;

#define all(v) v.begin(), v.end()

void BestLoc(const vector<psb>& BestNames, unordered_map<string, int>& Result) {
    int Count = 1;
    for (const psb& p : BestNames) {
        if (p.second) Count++;
        else Result[p.first] = Count;
    }
    return;
}

int main() {
    int N;
    vector<string> LowestNames, HighestNames;
    vector<psb> BestNames;
    unordered_map<string, int> Lowest, Highest;
    cin >> N;
    for (int i = 0; i < N; i++) {
        string Name;
        cin >> Name;
        sort(all(Name));
        LowestNames.push_back(Name);
        BestNames.push_back({Name, false});
        reverse(all(Name));
        HighestNames.push_back(Name);
        BestNames.push_back({Name, true});
    }
    sort(all(BestNames));
    BestLoc(BestNames, Lowest);
    reverse(all(BestNames));
    for (psb& p : BestNames) p.second = (not p.second);
    BestLoc(BestNames, Highest);
    for (int i = 0; i < N; i++) cout << Lowest[LowestNames[i]] << " " << N + 1 - Highest[HighestNames[i]] << "\n";
    return 0;
}
