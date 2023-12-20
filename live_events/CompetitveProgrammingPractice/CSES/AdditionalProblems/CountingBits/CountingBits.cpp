#include <iostream>
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

ll n, ans = 0;

int main() {
    cin >> n;
    for (ll i = 1; i <= n; i <<= 1) {
        ans += (n + 1) / (2 * i) * i;
        if ((n + 1) / i % 2 == 1) ans += n - (n + 1) / i * i + 1;
    }
    cout << ans << "\n";
	return 0;
}
