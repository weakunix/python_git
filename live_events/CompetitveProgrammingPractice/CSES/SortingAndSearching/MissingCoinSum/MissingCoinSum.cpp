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

int n;
ll ans = 1;
map<ll, int> coins;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        coins[cur]++;
    }
    for (auto& u : coins) {
        if (ans < u.first) break;
        ans += u.first * u.second;
    }
    cout << ans << "\n";
	return 0;
}
