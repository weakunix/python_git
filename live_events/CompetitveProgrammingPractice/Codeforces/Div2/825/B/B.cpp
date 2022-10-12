#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

void Subcase() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i + 2 < n; i++) {
        if (lcm(gcd(a[i], a[i + 2]), a[i + 1]) != a[i + 1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) Subcase();
	return 0;
}
