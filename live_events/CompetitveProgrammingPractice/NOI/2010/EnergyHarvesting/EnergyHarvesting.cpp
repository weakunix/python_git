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

const int N = 1e5 + 1;

int n, m;
ll cnt[N], ans = 0;

int main() {
    clr(cnt, 0);

    cin >> n >> m;

    for (int i = n; i > 0; i--) {
        cnt[i] = (ll) (n / i) * (m / i);
        for (int j = i + i; j <= n; j += i) cnt[i] -= cnt[j];
        ans += cnt[i] * (2 * i - 1);
    }

    cout << ans << "\n";

	return 0;
}
