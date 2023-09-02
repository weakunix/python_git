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

const int X = 2e6 + 5, modval = 1e9 + 7;

int n, m;
ll fac[X];

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

int main() {
    fac[0] = 1;
    for (int i = 1; i < X; i++) fac[i] = fac[i - 1] * i % modval;

    cin >> n >> m;
    cout << fac[n + m - 1] * modinv(fac[n - 1]) % modval * modinv(fac[m]) % modval << "\n";
	return 0;
}
