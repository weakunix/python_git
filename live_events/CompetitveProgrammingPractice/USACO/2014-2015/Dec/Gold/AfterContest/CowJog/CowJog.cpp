#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()

int main() {
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);

    int N, T;
    vector<ll> Ends, Dp;
    cin >> N >> T;

    for (int i = 0; i < N; i++) {
        ll Start, Speed;
        cin >> Start >> Speed;
        Ends.push_back(Start + (T * Speed));
    }

    reverse(all(Ends));

    for (ll i : Ends) {
        int Idx = upper_bound(Dp.begin(), Dp.end(), i) - Dp.begin();
        if (Idx == Dp.size()) Dp.push_back(i);
        else Dp[Idx] = i;
    }

    cout << Dp.size() << "\n";

    return 0;
}
