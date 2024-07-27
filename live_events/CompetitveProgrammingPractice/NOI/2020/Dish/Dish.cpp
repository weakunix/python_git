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
#include <bitset>
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

const int N = 501, K = 5000, S = N * K;

int t, n, m, k, arr[N];
bitset<2 * S + 1> dp[N];

void solve(set<simps>& s) {
    while (s.size() > 1) {
        auto it1 = s.begin(), it2 = s.end();
        it2--;

        int cnt1 = it1->first, idx1 = it1->second, cnt2 = it2->first, idx2 = it2->second;

        assert((cnt1 > 0 and cnt1 < k) and cnt1 + cnt2 >= k);
        s.erase(it1);
        s.erase(it2);
        s.insert({cnt2 - (k - cnt1), idx2});
        cout << idx1 << " " << cnt1 << " " << idx2 << " " << k - cnt1 << "\n";
    }
    return;
}

void subcase() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> arr[i];

    if (m == n - 2) {
        dp[0].reset();
        dp[0].set(S);
        for (int i = 1; i <= n; i++) {
            if (arr[i] >= k) dp[i] = dp[i - 1] | (dp[i - 1] << (arr[i] - k));
            else dp[i] = dp[i - 1] | (dp[i - 1] >> (k - arr[i]));
        }

        if (not dp[n][S - k]) {
            cout << "-1\n";
            return;
        }

        int cur = S - k;
        set<simps> a, b;
        for (int i = n; i > 0; i--) {
            if (dp[i - 1][cur]) {
                a.insert({arr[i], i});
                continue;
            }
            b.insert({arr[i], i});
            cur -= arr[i] - k;
        }

        solve(a);
        solve(b);
        return;
    }

    set<simps> s;
    for (int i = 1; i <= n; i++) s.insert({arr[i], i});

    for (; m >= n; m--) {
        auto it = s.end();
        it--;
        
        int cnt = it->first, idx = it->second;

        if (cnt == k) {
            assert(m == n);
            for (simps i : s) {
                assert(i.first == k);
                cout << i.second << " " << k << "\n";
            }
            return;
        }

        assert(cnt > k);
        s.erase(it);
        s.insert({cnt - k, idx});
        cout << idx << " " << k << "\n";
    }

    solve(s);

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
