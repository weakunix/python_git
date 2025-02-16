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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 1;

int n, k, q, arr[N];
ll ans = 0;
multiset<int> good, bad;

int getsmall(multiset<int>& s) {
    return *s.begin();
}

int getbig(multiset<int>& s) {
    auto it = s.end();
    it--;
    return *it;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    clr(arr, 0);

    cin >> n >> k >> q;

    for (int i = 1; i <= k; i++) good.insert(0);
    for (int i = k + 1; i <= n; i++) bad.insert(0);
    bad.insert(-1);

    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        
        if (good.count(arr[x])) {
            good.erase(good.find(arr[x]));
            good.insert(y);
            ans += y - arr[x];
        }
        else {
            bad.erase(bad.find(arr[x]));
            bad.insert(y);
        }
        
        int l = getsmall(good), g = getbig(bad);
        if (l < g) {
            good.erase(good.find(l));
            bad.erase(bad.find(g));
            good.insert(g);
            bad.insert(l);
            ans += g - l;
        }

        arr[x] = y;

        cout << ans << "\n";
    }

	return 0;
}
