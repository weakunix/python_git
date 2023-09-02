#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
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

int n, m;
ll pw[N], ans = 0;

ll modinv(ll a) {
    int b = modval - 2;
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

int main() {
    cin >> n >> m;
    pw[0] = 1;
    for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * m % modval;
    for (int i = 1; i <= n; i++) ans = (ans + pw[gcd(i, n)]) % modval;
    cout << ans * modinv(n) % modval << "\n";
	return 0;
}
