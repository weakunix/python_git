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

void subcase() {
    int n, g, res;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i == 0) g = a[i];
        else g = gcd(a[i], g);
    }
    if (g == 1) {
        cout << "0\n";
        return;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (gcd(gcd(a[i], i + 1), g) == 1) {
             res = n - i;
             break;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            if (gcd(gcd(gcd(a[i], i + 1), gcd(a[j], j + 1)), g) == 1) res = min(n - i + n - j, res);
        }
    }

    cout << res << "\n";

    return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
