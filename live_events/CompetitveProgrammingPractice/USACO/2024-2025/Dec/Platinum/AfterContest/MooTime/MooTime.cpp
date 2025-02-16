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

const int N = 3e5;

struct Range {
    vector<ll> cost[3][3]; //0 normal, 1 rem 1, 2 add 1
    
    Range() {}

    ~Range() {}
};

int n, l, c[N];
ll moo[N];
bool s[N];

void merge(vector<ll>& tar, vector<ll>& a, vector<ll>& b) {
    int lidx = 0, ridx = 0;

    while (true) {
        tar.pb(a[lidx] + b[ridx]);
        if (lidx == a.size() - 1 and ridx == b.size() - 1) break;
        if (lidx == a.size() - 1) ridx++;
        else if (ridx == b.size() - 1) lidx++;
        else if (a[lidx + 1] + b[ridx] < a[lidx] + b[ridx + 1]) lidx++;
        else ridx++;
    }

    return;
}

Range dp(int le, int ri) {
    int len = ri - le + 1;
    Range res;

    if (len <= l) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (l == 1 and (i != 0 or j != 0)) continue;

                int a = max(le + (i == 1) - (i == 2), 0), b = min(ri - (j == 1) + (j == 2), n - 1);

                res.cost[i][j].pb(0);

                ll best = 1e18;
                for (int k = a; k + l - 1 <= b; k++) setmn(best, moo[k]);
                if (best != 1e18) res.cost[i][j].pb(best);
            }
        }
        return res;
    }

    int mid = le + (ri - le) / 2;
    Range lrng = dp(le, mid), rrng = dp(mid + 1, ri);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (l == 1 and (i != 0 or j != 0)) continue;

            vector<ll> cur1, cur2, cur3;
            merge(cur1, lrng.cost[i][0], rrng.cost[0][j]);
            if (l > 1 and le < mid) merge(cur2, lrng.cost[i][1], rrng.cost[2][j]);
            if (l > 1 and mid + 1 < ri) merge(cur3, lrng.cost[i][2], rrng.cost[1][j]);

            int curlen = min(ri - (j == 1) + (j == 2), n - 1) - max(le + (i == 1) - (i == 2), 0) + 1;
            while (cur1.size() <= curlen) cur1.pb(1e18);
            while (cur2.size() <= curlen) cur2.pb(1e18);
            while (cur3.size() <= curlen) cur3.pb(1e18);
            for (int k = 0; k <= curlen / l; k++) res.cost[i][j].pb(min({cur1[k], cur2[k], cur3[k]}));
        }
    }

    return res;
}

int main() {
    cin >> l >> n;
    for (int i = 0; i < n; i++) {
        char cur;
        cin >> cur;
        s[i] = (cur == 'M');
    }
    for (int i = 0; i < n; i++) cin >> c[i];

    for (int i = 0; i < n - l + 1; i++) {
        moo[i] = (s[i] ? 0 : c[i]);
        for (int j = i + 1; j < i + l; j++) moo[i] += (s[j] ? c[j] : 0);
    }

    Range ans = dp(0, n - 1);

    for (int i = 1; i <= n / l; i++) cout << ans.cost[0][0][i] << "\n";

	return 0;
}
