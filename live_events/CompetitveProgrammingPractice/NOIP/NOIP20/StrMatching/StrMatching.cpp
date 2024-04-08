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

const int N = (1 << 20) + 1, B = 41, modval = 1e9 + 7;

int t, n, pfx[N], sfx[N], sz[N], lst[N], prv[27];
ll pw[N], hsh[N], ans;
bool seen[26];
string s;

void subcase() {
    ans = 0;
    clr(sz, -1);
    clr(prv, 0);

    cin >> s;
    n = s.size();
    s = '#' + s;

    int cnt = 0;
    clr(seen, false);
    for (int i = 1; i <= n; i++) {
        int cur = s[i] - 'a';
        if (seen[cur]) cnt--;
        else cnt++;
        seen[cur] = not seen[cur];
        pfx[i] = cnt;
    }

    cnt = 0;
    clr(seen, false);
    for (int i = n; i > 0; i--) {
        int cur = s[i] - 'a';
        if (seen[cur]) cnt--;
        else cnt++;
        seen[cur] = not seen[cur];
        sfx[i] = cnt;
    }

    hsh[0] = 0;
    for (int i = 1; i <= n; i++) hsh[i] = (hsh[i - 1] + pw[i - 1] * (s[i] - 'a' + 1)) % modval;

    for (int i = 1; i <= n; i++) {
        if (sz[i] == -1) sz[i] = i;
        lst[sz[i]] = i;
        if (i + sz[i] <= n and hsh[sz[i]] * pw[i] % modval == (hsh[i + sz[i]] + modval - hsh[i]) % modval) sz[i + sz[i]] = sz[i];
    }

    for (int i = 2; i < n; i++) {
        for (int j = pfx[i - 1]; j <= 26; j++) prv[j]++;
        int cur = lst[sz[i]] / i;
        ans += prv[sfx[i + 1]] * (cur / 2 + cur % 2);
        if (cur > 1) ans += prv[sfx[2 * i + 1]] * (cur / 2);

        if (cur * i == n) {
            if (cur % 2) ans -= prv[sfx[i + 1]];
            else ans -= prv[sfx[2 * i + 1]];
        }
    }

    cout << ans << "\n";

	return;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(0), cout.tie(0);

    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = B * pw[i - 1] % modval;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();

	return 0;
}
