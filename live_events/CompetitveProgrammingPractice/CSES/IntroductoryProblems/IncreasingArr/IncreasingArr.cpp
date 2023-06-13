#include <iostream>
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

int n;
ll ans = 0;
vector<int> arr;

int main() {
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 1; i < n; i++) {
        if (arr[i] >= arr[i - 1]) continue;
        ans += arr[i - 1] - arr[i];
        arr[i] = arr[i - 1];
    }
    cout << ans << "\n";
	return 0;
}
