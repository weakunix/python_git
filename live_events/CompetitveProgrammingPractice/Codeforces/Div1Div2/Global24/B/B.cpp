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
#define rall(v) v.rbegin(), v.rend()

void subcase() {
    int n, g = -1, mx = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (g == -1) g = cur;
        else g = gcd(cur, g);
        mx = max(cur, mx);
    }
    cout << mx / g << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
