#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int L = 30;

int t;

void subcase() {
    int n;
    ll ans = 0;
    cin >> n;
    vector<int> arr(n);
    vector<ll> lodd(L, 0), leven(L, 0), rodd(L, 0), reven(L, 0);
    vector<vector<int>> bits(n);

    vector<bool> isodd(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        for (int j = 0; j < L; j++) {
            if ((1 << j) & arr[i]) {
                bits[i].pb(j);
                isodd[j] = not isodd[j];
            }
            if (isodd[j]) rodd[j]++;
            else reven[j]++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < L; j++) leven[j]++;
        for (int j : bits[i]) swap(lodd[j], leven[j]);

        int hi = bits[i].back();
        ans += lodd[hi] * reven[hi] + leven[hi] * rodd[hi];

        for (int j : bits[i]) swap(rodd[j], reven[j]);
        for (int j = 0; j < L; j++) reven[j]--;
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
