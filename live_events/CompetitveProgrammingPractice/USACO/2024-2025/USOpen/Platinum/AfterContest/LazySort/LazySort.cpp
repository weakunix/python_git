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

const int N = 5e6 + 1, Q = 101, modval = 1e9 + 7;
ll fact[N], invfact[N];

int n, q, c[Q], v[Q];
ll ans1 = 1, ans2 = 0, curchoose[Q];

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll choose(int a, int b) { //a choose b
    if (b > a) return 0;
    if (b < 0) return 0;
    return fact[a] * invfact[b] % modval * invfact[a - b] % modval;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i % modval;
    invfact[N - 1] = pw(fact[N - 1], modval - 2);
    for (int i = N - 2; i >= 0; i--) invfact[i] = invfact[i + 1] * (i + 1) % modval;

    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        cin >> c[i] >> v[i];
        c[i]--;
        v[i] += c[i];
    }

    for (int i = 0; i < q - 1; i++) {
        int k = c[i + 1] - c[i];
        ll newans1 = 0, newans2 = 0;

        curchoose[0] = 1;
        for (int i = 1; i < k; i++) curchoose[i] = curchoose[i - 1] * (c[i + 1] - cur[i] - i) % modval;
        for (int i = 1; i < k; i++) curchoose[i] = curchoose[i] * invfact[i] % modval;    

        for (int x = 0; x <= k; x++) { //1
            for (int y = 0; x + y <= k; y++) { //0
                curchoose[k - x
            }
        }
    }

    cout << ans1 + ans2 << "\n";

	return 0;
}
