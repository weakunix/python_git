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

const int N = 1e5;

ll n, edges[N], pfx[N], ppfx[N], val, ans = 1e18;

int main() {
    pfx[0] = 0;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> edges[i];
    val = edges[0] - edges[n - 1];
    for (int i = 1; i < n; i++) pfx[i] = pfx[i - 1] + edges[i] - edges[i - 1];

    if (val < 0) val = -val;
    for (int i = 0; i < n; i++) pfx[i] = -pfx[i];

    sort(pfx, pfx + n);

    ppfx[0] = pfx[0];
    for (int i = 1; i < n; i++) ppfx[i] = ppfx[i - 1] + pfx[i];

    for (int i = -2e4; i <= 2e4; i++) {
        ll idx = ub(pfx, pfx + n, i) - pfx, cur = 0;
        cur = idx * i - ppfx[idx - 1];
        cur += ppfx[n - 1] - ppfx[idx - 1] - (n - idx) * i;
        setmn(ans, cur);
    }

    cout << ans << "\n";

	return 0;
}
