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

const int N = 2e5;

int t, arr[N];

void subcase() {
    int n;
    ll ans = 0;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = n - 2; i >= 0; i--) {
        int l = 1, r = 1e9;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[i] / mid + (arr[i] % mid != 0) <= arr[i + 1]) r = mid;
            else l = mid + 1;
        }
        ans += l - 1;
        arr[i] /= l;
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
