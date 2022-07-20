#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define rall(v) v.rbegin(), v.rend()

int main() {
    int L, N, F, B, CurLoc = 0;
    ll Ans = 0;
    cin >> L >> N >> F >> B;
    vector<pii> Stores(N);
    for (int i = 0; i < N; i++) cin >> Stores[i].second >> Stores[i].first;
    sort(rall(Stores));
    for (const pii& p : Stores) {
        if (p.second > CurLoc) {
            int Dist = p.second - CurLoc;
            Ans += (ll) (F - B) * Dist * p.first;
            CurLoc = p.second;
        }
    }
    cout << Ans << "\n";
    return 0;
}
