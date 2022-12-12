#include <iostream>
#include <string>
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

void subcase() {
    int n, mn = 1e9, mx = 0, mncount = 0, mxcount = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (cur == mn) mncount++;
        else if (cur < mn) {
            mn = cur;
            mncount = 1;
        }
        if (cur == mx) mxcount++;
        else if (cur > mx) {
            mx = cur;
            mxcount = 1;
        }
    }
    cout << ((mn == mx) ? (ll) n * (n - 1) : (ll) 2 * mncount * mxcount) << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
