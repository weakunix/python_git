#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

void subcase() {
    int n;
    ll pairs = 0, lone, ans;
    vector<int> arr;
    map<int, int> lo, hi;
    cin >> n;
    lone = n % 2;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(all(arr));
    for (int i = 0; i < n / 2; i++) {
        if (arr[i] < arr[n - i - 1]) {
            pairs++;
            lo[arr[i]] = i + 1;
            hi[arr[n - i - 1]] = i + 1;
        }
        else lone += 2;
    }
    ans = pairs * pairs;
    if (lone > 0) {
        int val = arr[n / 2];
        ll best = lone / 2;
        auto it1 = lo.lower_bound(val), it2 = hi.upper_bound(val);
        if (it1 != lo.begin()) {
            it1--;
            best = max(lone * it1->second, best);
        }
        if (it2 != hi.end()) best = max(lone * it2->second, best);
        ans += best;
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
