#include <iostream>
#include <string>
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

const int X = 2e6 + 1, modval = 1e9 + 7;

int n, cnt = 0;
ll fac[X];
string s;

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

ll choose(int a, int b) {
    if (a < b) return 0;
    return fac[a] * modinv(fac[b]) % modval * modinv(fac[a - b]) % modval;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < X; i++) fac[i] = fac[i - 1] * i % modval;

    cin >> n >> s;
    if (n % 2) {
        cout << "0\n";
        return 0;
    }
    for (char c : s) {
        cnt += (c == '(' ? 1 : -1);
        if (cnt < 0) {
            cout << "0\n";
            return 0;
        }
    }
    if (s.size() == n) {
        cout << (cnt == 0) << "\n";
        return 0;
    }
    n = (n + cnt - s.size()) / 2;
    cout << (choose(2 * n - cnt, n) + modval - choose(2 * n - cnt, n + 1)) % modval << "\n";
	return 0;
}
