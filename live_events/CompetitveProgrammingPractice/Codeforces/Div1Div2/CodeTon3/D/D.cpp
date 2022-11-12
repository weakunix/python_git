#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

const int modval = 998244353;

vector<int> getpf(int val) {
    vector<int> res;
    for (int i = 2; i * i <= val; i++) {
        if (val % i == 0) res.push_back(i);
        while (val % i == 0) val /= i;
    }
    if (val > 1) res.push_back(val);
    return res;
}

void subcase() {
    int n, m;
    ll ans = 1;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i - 1] or arr[i - 1] % arr[i] != 0) {
            cout << "0\n";
            return;
        }
        int len;
        ll res = 0;
        vector<int> pf = getpf(arr[i - 1] / arr[i]);
        len = pf.size();
        for (int j = 0; j < 1 << len; j++) {
            ll cur = arr[i];
            for (int k = 0; k < len; k++) {
                if ((1 << k) & j) cur *= -pf[k];
            }
            res += m / cur;
        }
        assert(res >= 0);
        ans = (ans * res) % modval;
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
