#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using index_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;

#define ook order_of_key

int N;
ll CurCross = 0, Ans;
vector<int> Top, Bottom, TopIdx, BottomIdx;

void FindStartCross() {
    index_set<int> Prev;

    for (int i : Top) {
        CurCross += Prev.size() - Prev.ook(BottomIdx[i]);
        Prev.insert(BottomIdx[i]);
    }

    Ans = CurCross;

    return;
}

int main() {
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);

    cin >> N;
    Top.resize(N);
    Bottom.resize(N);
    TopIdx.resize(N);
    BottomIdx.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> Top[i]; Top[i]--;
        TopIdx[Top[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        cin >> Bottom[i]; Bottom[i]--;
        BottomIdx[Bottom[i]] = i;
    }

    FindStartCross();
    
    for (int i = N - 1; i >= 0; i--) {
        CurCross += 2 * BottomIdx[Top[i]] - N + 1;
        Ans = min(CurCross, Ans);
    }

    for (int i = N - 1; i >= 0; i--) {
        CurCross += 2 * TopIdx[Bottom[i]] - N + 1;
        Ans = min(CurCross, Ans);
    }

    cout << Ans << "\n";

	return 0;
}
