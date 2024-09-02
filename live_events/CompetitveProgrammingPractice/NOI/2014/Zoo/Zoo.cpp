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

const int N = 1e6, modval = 1e9 + 7;

int t, kmp[N], cnt[N];

void subcase() {
    int n;
    string s;
    cin >> s;
    n = s.size();

    kmp[0] = 0;
    cnt[0] = 1;
    for (int i = 1, j = 0; i < n; i++) {
        while (j and s[i] != s[j]) j = kmp[j - 1];
        if (s[i] == s[j]) {
            cnt[i] = cnt[j] + 1;
            j++;
            kmp[i] = j;
        }
        else {
            kmp[i] = 0;
            cnt[i] = 1;
        }
    }

    ll ans = 1;
    for (int i = 1, j = 0; i < n; i++) {
        while (j and s[i] != s[j]) j = kmp[j - 1];
        if (s[i] != s[j]) continue;
        while (2 * (j + 1) > i + 1) j = kmp[j] - 1;
        ans = ans * (cnt[j] + 1) % modval;
        j++;
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
