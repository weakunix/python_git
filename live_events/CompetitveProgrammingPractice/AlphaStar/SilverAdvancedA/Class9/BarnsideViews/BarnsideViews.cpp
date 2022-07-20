#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define rall(v) v.rbegin(), v.rend()

int main() {
    int N;
    ll Ans = 0;
    vector<pii> Barns;
    set<int> AlrConsLoc;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int h;
        cin >> h;
        Barns.push_back({h, i});
    }
    sort(rall(Barns));
    for (const pii& p : Barns) {
        int CurLoc = p.second, Earliest = N;
        auto EarliestIt = AlrConsLoc.lower_bound(CurLoc);
        if (EarliestIt != AlrConsLoc.end()) Earliest = *EarliestIt;
        Ans += Earliest - CurLoc - 1;
        AlrConsLoc.insert(CurLoc);
    }
    cout << Ans << "\n";
    return 0;
}
