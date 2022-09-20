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

int N, K;
vector<int> Cows;
index_set<int> Done;

void GetK() {
    int High = 1e9;

    while (not Cows.empty() and Cows.back() < High) {
        High = Cows.back();
        Done.insert(High);
        Cows.pop_back();
        K--;
    }

    return;
}

int main() {
	freopen("sleepy.in", "r", stdin);
	freopen("sleepy.out", "w", stdout);

    cin >> N;
    K = N;
    Cows.resize(N);
    for (int i = 0; i < N; i++) cin >> Cows[i];

    GetK();

    cout << K << "\n";

    for (int i = 0; i < K; i++) {
        cout << K - i - 1 + Done.ook(Cows[i]);
        if (i < K - 1) cout << " ";
        Done.insert(Cows[i]);
    }

	return 0;
}
