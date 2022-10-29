#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, ans = 0;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(all(arr));
    for (int i = n - 1; i > 1; i--) ans = max(arr[i] - arr[0] + arr[i] - arr[i - 1], ans);
    for (int i = 0; i < n - 1; i++) ans = max(arr[n - 1] - arr[i] + arr[i + 1] - arr[i], ans);
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
