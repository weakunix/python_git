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

int t;

void subcase() {
    int n;
    ll initval = 0, ans, mn1 = -1;
    vector<simps> arr;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i].first;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].second;
        initval += abs(arr[i].first - arr[i].second);
    }
    ans = initval;
    sort(all(arr));

    for (int i = 0; i < n; i++) {
        if (arr[i].first <= arr[i].second and mn1 != -1) ans = max(initval + 2 * (arr[i].first - mn1), ans);
        if (arr[i].first >= arr[i].second and mn1 == -1) mn1 = arr[i].first;
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
