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
vector<int> Height;
index_set<int> Left, Right;

int main() {
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);

    cin >> N;
    Height.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> Height[i];
        Right.insert(Height[i]);
    }

    for (int i : Height) {
        Right.erase(i);

        int l = Left.size() - Left.ook(i), r = Right.size() - Right.ook(i);

        Ans += (min(l, r) * 2 < max(l, r));

        Left.insert(i);
    }
    
    cout << Ans << "\n";

    return 0;
}
