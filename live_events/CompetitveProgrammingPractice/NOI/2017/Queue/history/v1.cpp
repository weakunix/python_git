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
typedef pair<ll, ll> simps;
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

const int N = 2e5, K = 50, A = 6, modval = 998244353, H1 = 1e9 + 7, H2 = 1e9 + 9;
ll pw1[K + 1], pw2[K + 1];

int n, q, val[N], prv[N], nxt[N];
map<simps, int> mp[K];

int main() {
    pw1[0] = 1;
    pw2[0] = 1;
    for (int i = 1; i <= K; i++) {
        pw1[i] = pw1[i - 1] * A % H1;
        pw2[i] = pw2[i - 1] * A % H2;
    }

    clr(prv, -1);
    clr(nxt, -1);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        val[i]--;
        mp[0][make_pair(val[i], val[i])]++;
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            
            nxt[u] = v;
            prv[v] = u;
            
            int lcnt = 1;
            while (u != -1 and lcnt < K) {
                bool add = false;
                simps hsh = {0, 0};
                for (int j = u, rcnt = 0; j != -1 and rcnt < K; j = nxt[j], rcnt++) {
                    hsh.first = (hsh.first * A + val[j]) % H1;
                    hsh.second = (hsh.second * A + val[j]) % H2;
                    if (j == v) add = true;
                    if (add) mp[rcnt][hsh]++;
                }

                u = prv[u];
                lcnt++;
            }
        }
        else if (t == 2) {
            int u, v;
            cin >> u;
            u--;
            v = nxt[u];

            int lcnt = 1;
            while (u != -1 and lcnt < K) {
                bool sub = false;
                simps hsh = {0, 0};
                for (int j = u, rcnt = 0; j != -1 and rcnt < K; j = nxt[j], rcnt++) {
                    hsh.first = (hsh.first * A + val[j]) % H1;
                    hsh.second = (hsh.second * A + val[j]) % H2;
                    if (j == v) sub = true;
                    if (sub) mp[rcnt][hsh]--;
                }

                u = prv[u];
                lcnt++;
            }
            
            nxt[prv[v]] = -1;
            prv[v] = -1;
        }
        else {
            int k;
            ll ans = 1;
            simps hsh = {0, 0};
            string s;
            cin >> s >> k;
            for (int j = 0; j < k; j++) {
                hsh.first = (hsh.first * A + (s[j] - '1')) % H1;
                hsh.second = (hsh.second * A + (s[j] - '1')) % H2;
            }
            ans = ans * mp[k - 1][hsh] % modval;
            for (int j = k; j < s.size(); j++) {
                hsh.first = (hsh.first * A + (s[j] - '1')) % H1;
                hsh.second = (hsh.second * A + (s[j] - '1')) % H2;
                hsh.first = (hsh.first + H1 - (s[j - k] - '1') * pw1[k] % H1) % H1;
                hsh.second = (hsh.second + H2 - (s[j - k] - '1') * pw2[k] % H2) % H2;
                ans = ans * mp[k - 1][hsh] % modval;
            }
            cout << ans << "\n";
        }
    }

	return 0;
}
