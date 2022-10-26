#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<ll, simps> threesome;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<ll> sumpfx(n + 1), xorpfx(n + 1);
    vector<threesome> seg(2 * n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sumpfx[i + 1] = sumpfx[i] + a[i];
        xorpfx[i + 1] = xorpfx[i] ^ a[i];
    }
    for (int i = n + 1; i <= 2 * n; i++) seg[i] = {0, {a[i - n - 1], a[i - n - 1]}};
    for (int i = n; i > 0; i--) {
        int a = i / 2, b = i / 2 + 1;
        seg[i] = minseg(seg[a], seg[b]);
    }
    
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
