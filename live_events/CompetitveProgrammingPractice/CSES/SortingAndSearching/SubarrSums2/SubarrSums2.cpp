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

int n, tar;
ll ans = 0;
vector<ll> pfx = {0};
map<ll, int> cnt;

int main() {
    cin >> n >> tar;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        pfx.push_back(pfx.back() + cur);
    }
    for (ll i : pfx) {
        ans += cnt[i - tar];
        cnt[i]++;
    }
    cout << ans << "\n";
	return 0;
}
