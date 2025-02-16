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

const int N = 1e5 + 1;

int n, a[N];
ll psbl[N], cur = 1, ans = 0;

int main() {
    cin >> n;
    for (int i = 0; i <= n; i++) cin >> a[i];
    psbl[n] = a[n];
    for (int i = n - 1; i >= 0; i--) psbl[i] = psbl[i + 1] + a[i];
    for (int i = 0; i <= n; i++) {
        if (cur < a[i]) {
            cout << "-1\n";
            return 0;
        }
        ans += cur;
        if (i < n) {
            cur = min(2 * (cur - a[i]), psbl[i + 1]);
        }
    }
    cout << ans << "\n";

	return 0;
}
