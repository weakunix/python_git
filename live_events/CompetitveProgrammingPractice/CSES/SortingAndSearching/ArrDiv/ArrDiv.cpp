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

int n, k;
ll l = 1, r = 2e14;
vector<int> arr;

bool works(ll tar) {
    int cnt = 1;
    ll cur = 0;
    for (int i : arr) {
        if (cur + i <= tar) cur += i;
        else {
            cnt++;
            cur = i;
            if (cur > tar) return false;
        }
    }
    return cnt <= k;
}

int main() {
    cin >> n >> k;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (works(mid)) r = mid;
        else l = mid + 1;
    }
    assert(l == r);
    cout << l << "\n";
	return 0;
}
