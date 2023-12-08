#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef __uint128_t L;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 7501;

struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64);
		ull r = a - q * b;
		return r >= b ? r - b : r;
	}
};

int n, m;
bool prime[N];
ll fact[N], choose[N][N], dp1[N], dp2[N], ans = 1;

ll pw(ll a, ll b, ll modval) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        a = a * a % modval;
        b >>= 1;
    }
    return res;
}

int main() {
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    
    memset(prime, true, sizeof(prime));

    cin >> n >> m;

    FastMod fm = FastMod(m - 1);

    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fm.reduce(fact[i - 1] * i);

    for (int i = 0; i <= n; i++) {
        choose[i][0] = 1;
        choose[i][i] = 1;
        for (int j = 1; j < i; j++) choose[i][j] = fm.reduce(choose[i - 1][j - 1] + choose[i - 1][j]);
    }

    for (int i = 2; i <= n; i++) {
        if (not prime[i]) continue;
        for (int j = i * i; j <= n; j += i) prime[j] = false;

        ll cnt = 0;

        for (int j = i; j <= n; j *= i) {
            int mx = n / j, rem = n % j;

            dp1[0] = 1;
            for (int k = 1; k <= mx; k++) {
                dp1[k] = 0;
                for (int l = 1; l <= k; l++) dp1[k] = fm.reduce(dp1[k] + fm.reduce(fm.reduce(choose[k * j - 1][l * j - 1] * fact[l * j - 1]) * dp1[k - l]));
            }

            dp2[0] = fact[rem];
            for (int k = 1; k <= mx; k++) {
                dp2[k] = 0;
                for (int l = 1; l <= k; l++) dp2[k] = fm.reduce(dp2[k] + fm.reduce(fm.reduce(choose[rem + k * j][l * j] * dp1[l]) * dp2[k - l]));
                
                if (k < mx) dp2[k] = fm.reduce(fact[rem + k * j] + m - 1 - dp2[k]);
                else cnt = fm.reduce(cnt + dp2[k]);
            }
        }

        ans = (ans * pw(i, cnt, m)) % m;
    }

    cout << ans << "\n";
    
	return 0;
}
