#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int modval = 1e9 + 7;

ll n, mx, prv, sz = 2, ans = 0;

ll sm(ll num) {
    if (num % 2 == 0) return (num / 2 % modval) * ((num + 1) % modval) % modval;
    return ((num + 1) / 2 % modval) * (num % modval) % modval;
}

int main() {
    cin >> n;
    mx = sqrtl(n);
    prv = n;
    for (int i = 1; i <= mx; i++) ans = (ans + n / i * i) % modval;
    while (prv > mx) {
        ll cur = max(n / sz, mx);
        ans = (ans + (sm(prv) + modval - sm(cur)) % modval * (sz - 1) % modval) % modval;
        prv = cur;
        sz++;
    }
    cout << ans << "\n";
	return 0;
}
