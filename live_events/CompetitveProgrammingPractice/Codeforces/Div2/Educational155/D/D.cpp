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

const int N = 3e5, L = 30, modval = 998244353;

int n, a[N];
ll ans = 0;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < L; i++) {
        int cnt0 = 1, cnt1 = 0, xorval = false;
        ll val0 = 1, val1 = 0, res = 0;

        for (int j = 0; j < n; j++) {
            bool cur = (a[j] & (1 << i));
            xorval = (cur xor xorval);
            if (xorval) {
                res = (res + val0) % modval;
                cnt1++;
            }
            else {
                res = (res + val1) % modval;
                cnt0++;
            }

            val0 = (val0 + cnt0) % modval;
            val1 = (val1 + cnt1) % modval;
        }

        ans = (ans + res * (1 << i) % modval) % modval;
    }

    cout << ans << "\n";

	return 0;
}
