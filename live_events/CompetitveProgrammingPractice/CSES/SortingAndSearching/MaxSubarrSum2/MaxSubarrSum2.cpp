#include <iostream>
#include <vector>
#include <utility>
#include <set>
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

int n, a, b;
ll ans = -2e14;
vector<ll> pfx = {0};
multiset<ll> prv;

int main() {
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        pfx.push_back(pfx.back() + cur);
    }
    for (int i = a; i <= n; i++) {
        prv.insert(pfx[i - a]);
        if (i > b) prv.erase(prv.find(pfx[i - b - 1]));
        ans = max(pfx[i] - *prv.begin(), ans);
    }
    cout << ans << "\n";
	return 0;
}
