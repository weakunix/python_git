#include <iostream>
#include <vector>
#include <utility>
#include <map>
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

int n, k, l = 0, r = 0, prv = -1;
ll ans = 0;
vector<int> arr;
map<int, int> cnt;

int main() {
    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cnt[arr[0]] = 1;
    while (r < n) {
        if (cnt.size() <= k and r != prv) {
            ans += r - l + 1;
            prv = r;
        }
        if (cnt.size() <= k) {
            r++;
            cnt[arr[r]]++;
        }
        else {
            cnt[arr[l]]--;
            if (cnt[arr[l]] == 0) cnt.erase(arr[l]);
            l++;
        }
    }
    cout << ans << "\n";
	return 0;
}
