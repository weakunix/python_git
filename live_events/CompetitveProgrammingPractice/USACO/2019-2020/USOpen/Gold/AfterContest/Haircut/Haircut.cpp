#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> simps;
typedef tree<simps, null_type, less<simps>, rb_tree_tag, tree_order_statistics_node_update> simps_indexset;

#define ook order_of_key

int N;
vector<ll> Ans;
simps_indexset Prev;

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);

    cin >> N;
    Ans.resize(N);
    for (int i = 0; i < N; i++) {
        simps Cur = {0, i};

        cin >> Cur.first;
        
        Prev.insert(Cur);

        if (Cur.first + 1 < N) Ans[Cur.first + 1] += i - Prev.ook(Cur);
    }

    for (int i = 0; i < N; i++) {
        if (i > 0) Ans[i] += Ans[i - 1];

        cout << Ans[i] << "\n";
    }

    return 0;
}
