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

const int N = 1001, M = 9000, modval = 1e9 + 7;

struct Trans {
    int k, m;
    vector<bool> psbl;
    vector<vector<int>> nxt;
    map<ll, int> mp;
    
    Trans() : k(0), m(0) {}

    Trans(int _k) : k(_k), m(0) {
        ll st = 0;
        for (int i = 0; i < 8; i++) st = (k + 2) * st + k + 1;
        st *= (k + 2);
        build(st);
        return;
    }

    ~Trans() {}

    int build(ll st) {
        if (mp.count(st)) return mp[st];

        int cur = m;
        m++;
        mp[st] = cur;
        psbl.pb(st % (k + 2) != k + 1);
        nxt.pb(vector<int>(9));

        int f[2][3][3];

        for (int d = 0; d < 9; d++) {
            ll curst = st;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    f[0][i][j] = curst % (k + 2);
                    curst /= k + 2;
                    f[1][i][j] = k + 1;
                }
            }

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (f[0][i][j] == k + 1) continue;

                    for (int l = 0; l < 3; l++) {
                        for (int o = 0; o <= i; o++) {
                            int nxti = i + j - o;
                            if (nxti > 2) continue;

                            int req = d - i - j - l;
                            setmn(f[1][nxti][l], f[0][i][j] + max(-req, 0) + (req == 1));
                        }
                    }
                }
            }
            
            for (int i = 2; i >= 0; i--) for (int j = 2; j >= 0; j--) curst = curst * (k + 2) + f[1][i][j];
            nxt[cur][d] = build(curst);
        }

        return cur;
    }
};

int t, n, k, l[N], r[N];
ll g[2][M], ans;
bool all0, all1;

void subcase() {
    cin >> n >> k;
    all0 = (k == 1);
    all1 = (k == 1 and n == 3);
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        if (l[i] > 0) all0 = false;
        if (r[i] < 1 or l[i] > 1) all1 = false;
    }

    Trans trans(k);
    
    clr(g, 0);
    g[0][0] = 1;

    int prv = 1, nxt = 0;
    for (int i = 1; i <= n; i++) {
        swap(prv, nxt);
        clr(g[nxt], 0);

        for (int j = 0; j < trans.m; j++) {
            for (int o = l[i]; o <= min(r[i], 7); o++) g[nxt][trans.nxt[j][o]] = (g[nxt][trans.nxt[j][o]] + g[prv][j]) % modval;
            if (r[i] >= 8) g[nxt][trans.nxt[j][8]] = (g[nxt][trans.nxt[j][8]] + min(r[i] - 7, r[i] - l[i] + 1) * g[prv][j] % modval) % modval;
        }
    }

    ans = 0;
    for (int i = 0; i < trans.m; i++) if (trans.psbl[i]) ans = (ans + g[nxt][i]) % modval;
    cout << (ans + modval - all0 - all1) % modval << "\n";

    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
