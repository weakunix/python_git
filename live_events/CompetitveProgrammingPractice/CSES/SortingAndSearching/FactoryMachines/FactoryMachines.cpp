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

int n, t;
ll l = 1, r = 1e18;
vector<int> machines;

bool works(ll time) {
    ll cnt = 0;
    for (int i : machines) {
        cnt += time / i;
        if (cnt >= t) return true;
    }
    return false;
}

int main() {
    cin >> n >> t;
    machines.resize(n);
    for (int i = 0; i < n; i++) cin >> machines[i];
    while (l < r) {
        ll mid = l + (r - l) / 2;
        if (works(mid)) r = mid;
        else l = mid + 1;
    }
    assert(l == r);
    cout << l << "\n";
	return 0;
}
