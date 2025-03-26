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

const int N = 5e6, Q = 105, modval = 1e9 + 7;
ll fact[3 * Q], invfact[3 * Q];

int n, q, c[Q], v[Q];
ll ans0 = 1, ans1 = 0, pfx[2 * Q], invpfx[2 * Q];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll choose(int a, int b) {
    if (a < 0 or b < 0 or b > a) return 0;
    return fact[a] * invfact[b] % modval * invfact[a - b] % modval;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i < Q; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[Q - 1] = pw(fact[Q - 1], modval - 2);
    for (int i = Q - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

    cin >> n >> q;
    for (int i = 0; i < q; i++) cin >> c[i] >> v[i];
    for (int i = 0; i < q - 1; i++) {
        int k = c[i + 1] - c[i], a = v[i], b = v[i + 1];
        ll nw0 = 0, nw1 = 0;

        if (b - a < -1) {
            cout << "0\n";
            return 0;
        }
        if (b - a == -1) {
            ans1 = ans0 * k % modval;
            ans0 = 0;
            continue;
        }
        if (b - a == 0) {
            nw0 = ans0;
            nw1 = ans1;
        }

        if (b - a + k - 1 >= 3 * Q) {
            pfx[0] = b - a - k;
            for (int j = 1; j <= 2 * k; j++) pfx[j] = pfx[j - 1] * (b - a - k + j) % modval;
            invpfx[2 * k] = pw(pfx[2 * k], modval - 2);
            for (int j = 2 * k - 1; j >= 0; j--) invpfx[j] = invpfx[j + 1] * (b - a - k + j + 1) % modval;
        }

        for (int x = 0; k - x - 1 >= 0; x++) {
            for (int y = 0; k - x - y - 1 >= 0; y++) {
                ll c1;
                if (b - a + x - 1 < 3 * Q) c1 = choose(b - a + x - 1, k - x - y - 1);
                else {
                    int idx = (b - a + x - 1) - (b - a - k);
                    c1 = pfx[idx] * invpfx[idx - k - x - y - 1] % modval * invfact[k - x - y - 1] % modval;
                }

                ll c3 = choose(k, y);

                nw0 = (nw0 + ans0 * c1 % modval * choose(k - x - y, x) % modval * c3 % modval) % modval;
                nw0 = (nw0 + ans1 * c1 % modval * choose(k - x - y - 1, x) * c3 % modval) % modval;
                nw1 = (nw1 + ans0 * c1 % modval * choose(k - x - y, x - 1) % modval * c3 % modval) % modval;
                nw1 = (nw1 + ans1 * c1 % modval * choose(k - x - y - 1, x - 1) % modval * c3 % modval) % modval;
            }
        }

        swap(ans0, nw0);
        swap(ans1, nw1);
    }

    cout << (ans0 + ans1) % modval << "\n";

	return 0;
}
