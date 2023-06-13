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
ll sm = 0, ans = 1e14;
vector<ll> apples;

int main() {
    cin >> n;
    apples.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> apples[i];
        sm += apples[i];
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        ll cur = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) cur += apples[i];
        }
        ans = min(abs(sm - 2 * cur), ans);
    }
    cout << ans << "\n";
	return 0;
}
