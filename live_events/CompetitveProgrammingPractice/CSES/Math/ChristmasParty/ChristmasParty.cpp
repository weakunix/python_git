#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 1e6 + 1, modval = 1e9 + 7;

int n;
ll fac[N], ans = 0;

ll modinv(ll a) {
    int b = modval - 2;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll choose(int a, int b) {
    assert(a >= b);
    return fac[a] * modinv(fac[b]) % modval * modinv(fac[a - b]) % modval;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % modval;

    cin >> n;
    for (int i = 0; i <= n; i++) {
        ll cur = fac[n - i] * choose(n, i) % modval;
        if (i % 2) ans = (ans + modval - cur) % modval;
        else ans = (ans + cur) % modval;
    }
    cout << ans << "\n";
	return 0;
}
