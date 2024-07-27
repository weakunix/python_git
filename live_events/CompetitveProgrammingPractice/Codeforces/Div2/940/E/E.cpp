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

const int N = 1e6 + 1, modval = 1e9 + 7;

int t;
bool works[N];

void subcase() {
    int n;
    ll ans = 0;
    cin >> n;
    for (int j = 1; j <= n; j++) {
        if (not works[j] and j != 4) continue;
        int cnt = n - j + 1;
        ll cur = 1, res = 0;
        while (cnt >= j) {
            cnt -= j;
            if (j == 4) res += j * (2 * cur % j) % modval;
            else res += j * ((j - cur % j) % j) % modval;
            cur++;
        }
        if (j == 4) res += cnt * (2 * cur % j) % modval;
        else res += cnt * ((j - cur % j) % j) % modval;
        ans = (ans + res) % modval;
    }
    
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    clr(works, true);
    works[1] = false;
    for (int i = 2; i < N; i++) {
        if (not works[i]) continue;
        for (ll j = (ll) i * i; j < N; j += i) works[j] = false;
    }

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
