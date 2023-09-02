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

const int modval = 1e9 + 7;

ll n, ans = 0;

ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

int main() {
    cin >> n;
    ans = pw(2, n * n);
    if (n % 2) {
        ans = (ans + pw(2, (n * n - 1) / 2 + 1)) % modval;
        ans = (ans + pw(2, (n * n - 1) / 4 + 2)) % modval;
    }
    else {
        ans = (ans + pw(2, n * n / 2)) % modval;
        ans = (ans + pw(2, n * n / 4 + 1)) % modval;
    }
    cout << ans * pw(4, modval - 2) % modval << "\n";
	return 0;
}
