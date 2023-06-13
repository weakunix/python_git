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

int n, ans = 0;

int main() {
    cin >> n;
    for (ll i = 5; i <= n; i *= 5) ans += n / i;
    cout << ans << "\n";
	return 0;
}
