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

const int N = 1e6 + 1;

int n, m, best = 1e9;
simps arr[N];
ll dp[N], ans = 0;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> arr[i].first;
    for (int i = 0; i < n; i++) cin >> arr[i].second;
    sort(arr, arr + n);

    int idx = 0;
    dp[0] = 0;
    for (int i = 1; i < N; i++) {
        while (idx < n and arr[idx].first == i) {
            setmn(best, arr[idx].first - arr[idx].second);
            idx++;
        }
        if (best == 1e9) dp[i] = 0;
        else dp[i] = 2 + dp[i - best];
    }

    for (int i = 0; i < m; i++) {
        int c;
        cin >> c;
        if (c > 1e6) {
            int num = (c - 1e6) / best;
            ans += 2 * num;
            c -= best * num;
            if (c > 1e6) {
                ans += 2;
                c -= best;
            }
        }
        ans += dp[c];
    }

    cout << ans << "\n";

	return 0;
}
