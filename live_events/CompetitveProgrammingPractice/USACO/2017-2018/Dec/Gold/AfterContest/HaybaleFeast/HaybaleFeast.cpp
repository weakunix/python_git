#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

int N;
ll M;
vector<int> Flav, Spice;

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    cin >> N >> M;
    Flav.resize(N);
    Spice.resize(N);
    for (int i = 0; i < N; i++) cin >> Flav[i] >> Spice[i];

    
    int Left = 0, Ans = 1e9;
    ll CurFlav = 0;
    multiset<int> MaxSpice;

    for (int i = 0; i < N; i++) {
        CurFlav += Flav[i];
        MaxSpice.insert(Spice[i]);

        while (CurFlav >= M) {
            Ans = min(*MaxSpice.rbegin(), Ans);
            if (Left == i) break;
            CurFlav -= Flav[Left];
            MaxSpice.erase(MaxSpice.find(Spice[Left]));
            Left++;
        }
    }

    cout << Ans << "\n";

    return 0;
}
