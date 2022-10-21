#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

int pow2(int n) {
    int res = 0;
    while (n % 2 == 0) {
        n /= 2;
        res++;
    }
    return res;
}

void Subcase() {
    int n, curpow = 0, ans = 0;
    vector<int> a, add;
    cin >> n;
    a.resize(n);
    add.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        curpow += pow2(a[i]);
    }
    for (int i = 0; i < n; i++) add[i] = pow2(i + 1);
    sort(all(add));
    while (curpow < n) {
        if (add.empty()) {
            cout << "-1\n";
            return;
        }
        curpow += add.back();
        ans++;
        add.pop_back();
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
