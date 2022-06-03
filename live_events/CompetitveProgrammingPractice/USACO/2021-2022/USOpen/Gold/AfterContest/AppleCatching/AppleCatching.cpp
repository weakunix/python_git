#include <iostream>
#include <utility>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<int, int> simps;

#define lb(m, k) m.lower_bound(k)

bool OrderCows(simps a, simps b) {
    if (a.second == b.second) return a.first > b.first;
    return a.second > b.second;
}

int main() {
    int N, ApplesCaught = 0;
    map<simps, int> Apples, RemainingCows;
    map<simps, int, decltype(OrderCows)*> ConsideringCows(OrderCows);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int q, t, x, n;
        cin >> q >> t >> x >> n;
        if (q == 1) RemainingCows[make_pair(t + x, t - x)] = n;
        else Apples[make_pair(t + x, t - x)] = n;
    }
    while (Apples.size() > 0 and (RemainingCows.size() > 0 or ConsideringCows.size() > 0)) {
        auto CurApple = Apples.begin();
        while (RemainingCows.size() > 0) {
            auto CurCow = RemainingCows.begin();
            if (CurCow->first.first <= CurApple->first.first) {
                ConsideringCows[CurCow->first] = CurCow->second;
                RemainingCows.erase(CurCow->first);
            }
            else break;
        }
        auto CurCow = lb(ConsideringCows, CurApple->first);
        if (CurCow == ConsideringCows.end()) Apples.erase(CurApple->first);
        else {
            if (CurApple->second < CurCow->second) {
                ApplesCaught += CurApple->second;
                CurCow->second -= CurApple->second;
                Apples.erase(CurApple->first);
            }
            else if (CurApple->second > CurCow->second) {
                ApplesCaught += CurCow->second;
                CurApple->second -= CurCow->second;
                ConsideringCows.erase(CurCow->first);
            }
            else {
                ApplesCaught += CurApple->second;
                Apples.erase(CurApple->first);
                ConsideringCows.erase(CurCow->first);
            }
        }
    }
    cout << ApplesCaught << "\n";
    return 0;
}
