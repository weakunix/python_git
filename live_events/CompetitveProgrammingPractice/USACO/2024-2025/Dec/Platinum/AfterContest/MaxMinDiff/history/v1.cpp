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

const int N = 2000, modval = 1e9 + 7;

int t, n, k, val[N], idx[N];
ll ans;

void subcase() {
    ans = 0;

    clr(val, -1);
    clr(idx, -1);

    cin >> k;

    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        val[a] = b;
        idx[b] = a;
    }

    if (n % 2 == 0) {
        ans = 2;

        for (int i = 0; i < n; i++) {
            int cur = n / 2 - 1 - i / 2 + (i % 2 == 1 ? n / 2 : 0);
            if (val[i] == cur or val[i] == -1) continue;
            ans--;
            break;
        }

        for (int i = 0; i < n; i++) {
            int cur = n / 2 + i / 2 - (i % 2 == 1 ? n / 2 : 0);
            if (val[i] == cur or val[i] == -1) continue;
            ans--;
            break;
        }

        cout << ans << "\n";

        return;
    }

    assert(false); //FIXME

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> n;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
