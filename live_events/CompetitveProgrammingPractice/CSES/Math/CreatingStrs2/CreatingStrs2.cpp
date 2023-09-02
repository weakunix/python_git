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

const int C = 26, X = 1e6 + 1, modval = 1e9 + 7;

int cnt[C];
ll fac[X], ans;
string s;

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
    memset(cnt, 0, sizeof(cnt));
    fac[0] = 1;
    for (int i = 1; i < X; i++) fac[i] = fac[i - 1] * i % modval;

    cin >> s;
    for (char c : s) cnt[c - 'a']++;
    ans = fac[s.size()];
    for (int i = 0; i < C; i++) ans = ans * modinv(fac[cnt[i]]) % modval;
    cout << ans << "\n";
	return 0;
}
