#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, bool> pib;

void CloseIntervals(set<pib>& OriginalRabbitsSet) {
    auto Begin = OriginalRabbitsSet.begin(), End = OriginalRabbitsSet.end();
    End--;
    if (Begin->first != 1) OriginalRabbitsSet.insert({1, Begin->second});
    if (End->first != 1e9) OriginalRabbitsSet.insert({1e9, End->second});
    return;
}

int main() {
    int N, A, B, Count = 0;
    vector<pib> OriginalRabbits;
    set<pib> OriginalRabbitsSet;
    cin >> N >> A >> B;
    for (int i = 0; i < N; i++) {
        int Weight;
        bool IsSpotted;
        string Type;
        cin >> Type >> Weight;
        IsSpotted = (Type == "S");
        if (OriginalRabbitsSet.count({Weight, false}) > 0) {
            if (IsSpotted) {
                OriginalRabbitsSet.insert({Weight, true});
                OriginalRabbitsSet.erase({Weight, false});
            }
        }
        else if (OriginalRabbitsSet.count({Weight, true}) == 0) OriginalRabbitsSet.insert({Weight, IsSpotted});
    }
    CloseIntervals(OriginalRabbitsSet);
    for (const pib& p : OriginalRabbitsSet) OriginalRabbits.push_back(p);
    for (int i = 0; i <= N; i++) {
        int a = OriginalRabbits[i].first, b = OriginalRabbits[i + 1].first, Mid = a + (b - a) / 2;
        a++;
        b--;
        bool IsEven = ((b - a) % 2 == 0);
        if ((Mid - IsEven >= A and a <= B) and OriginalRabbits[i].second) Count += min(Mid - IsEven, B) - max(a, A) + 1;
        if ((b >= A and Mid + 1 <= B) and OriginalRabbits[i + 1].second) Count += min(b, B) - max(Mid + 1, A) + 1;
        if (IsEven) {
            if ((Mid >= A and Mid <= B) and (OriginalRabbits[i].second or OriginalRabbits[i + 1].second)) Count++;
        }
    }
    for (const pib& p : OriginalRabbits) {
        if ((p.first >= A and p.first <= B) and p.second) Count++;
    }
    cout << Count << "\n";
    return 0;
}
