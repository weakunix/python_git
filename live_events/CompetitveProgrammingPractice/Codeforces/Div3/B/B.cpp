#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void Subcase() {
    int n, q, odd = 0, even = 0;
    ll sum = 0;
    vector<int> a;
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        if (a[i] % 2 == 0) even++;
        else odd++;
    }
    for (int i = 0; i < q; i++) {
        int t, val;
        cin >> t >> val;
        if (t == 0) {
            sum += (ll) even * val;
            if (val % 2 == 1) {
                odd += even;
                even = 0;
            }
        }
        else {
            sum += (ll) odd * val;
            if (val % 2 == 1) {
                even += odd;
                odd = 0;
            }
        }
        cout << sum << "\n";
    }
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
