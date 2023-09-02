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

int n;

ll solve(ll a, int b, int m) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        b >>= 1;
        a = a * a % m;
    }
    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << solve(a, solve(b, c, modval - 1), modval) << "\n";
    }
	return 0;
}
