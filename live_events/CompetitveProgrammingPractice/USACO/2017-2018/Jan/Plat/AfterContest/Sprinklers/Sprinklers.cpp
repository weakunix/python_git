#include <iostream>
#include <cstdio>
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

const int N = 1e5, modval = 1e9 + 7;

/*
NOTATION

Equation (for given x, sum of): x * maxy - x * y - left(y) * maxy + left(y) * y

pfx1 on y * left(y)
pfx2 on left(y)

x * maxy: constant
x * y: constant
left(y) * maxy: maxy * pfx2
left(y) * y: pfx1
*/

int n;
ll miny[N], maxy[N], lft[N], pfx1[N], pfx2[N], ans = 0;

ll sm(ll num) {
    return num * (num + 1) / 2 % modval;
}

int main() {
    freopen("sprinklers.in", "r", stdin);
    freopen("sprinklers.out", "w", stdout);

    memset(maxy, 0, sizeof(maxy));
    fill(miny, miny + N, 1e9);
    fill(lft, lft + N, 1e9);
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        miny[x] = y;
        maxy[x] = y;
        lft[y] = x;
    }

    for (int i = 1; i < n; i++) miny[i] = min(miny[i - 1], miny[i]);
    for (int i = n - 2; i >= 0; i--) maxy[i] = max(maxy[i + 1], maxy[i]);
    for (int i = 1; i < n; i++) lft[i] = min(lft[i - 1], lft[i]);

    pfx1[0] = 0;
    for (ll i = 1; i < n; i++) pfx1[i] = (pfx1[i - 1] + i * lft[i]) % modval;

    pfx2[0] = lft[0];
    for (int i = 1; i < n; i++) pfx2[i] = (pfx2[i - 1] + lft[i]) % modval;

    for (int i = 0; i < n; i++) {
        if (miny[i] > maxy[i]) continue;

        ans = (ans + (ll) (maxy[i] - miny[i] + 1) * i % modval * maxy[i] % modval) % modval;
        ans = (ans - (sm(maxy[i]) - sm(miny[i] - 1)) % modval * i % modval) % modval;
        ans = (ans - (pfx2[maxy[i]] - (miny[i] > 0 ? pfx2[miny[i] - 1] : 0)) % modval * maxy[i]) % modval;
        ans = (ans + (pfx1[maxy[i]] - (miny[i] > 0 ? pfx1[miny[i] - 1] : 0)) % modval) % modval;

    }

    cout << (ans + modval) % modval << "\n";

	return 0;
}
