#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using index_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define ook order_of_key

int N, Ans = 0;
vector<int> FirstOccur;
index_set<int> StartIdx;

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    
    cin >> N;
    FirstOccur.resize(N, -1);
    for (int i = 0; i < 2 * N; i++) {
        int Cow; cin >> Cow; Cow--;

        if (FirstOccur[Cow] == -1) {
            FirstOccur[Cow] = i;
            StartIdx.insert(i);
            continue;
        }

        Cow = FirstOccur[Cow];
        
        StartIdx.erase(Cow);
        Ans += StartIdx.size() - StartIdx.ook(Cow);
    }

    cout << Ans << "\n";

    return 0;
}
