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

struct Mat {
    ll a, b, c, d;

    Mat(ll aa, ll bb, ll cc, ll dd) {
        a = aa; b = bb, c = cc; d = dd;
        return;
    }

    void operator*=(const Mat mat) {
        ll aa = (a * mat.a % modval + b * mat.c % modval) % modval;
        ll bb = (a * mat.b % modval + b * mat.d % modval) % modval;
        ll cc = (c * mat.a % modval + d * mat.c % modval) % modval;
        ll dd = (c * mat.b % modval + d * mat.d % modval) % modval;
        a = aa; b = bb; c = cc; d = dd;
        return;
    }
};

ll n;
Mat ans = Mat(1, 0, 0, 1), cur = Mat(1, 1, 1, 0);

int main() {
    cin >> n;
    if (n < 2) {
        cout << n << "\n";
        return 0;
    }
    n--;
    while (n) {
        if (n & 1) ans *= cur;
        n >>= 1;
        cur *= cur;
    }
    cout << ans.a << "\n";
	return 0;
}
