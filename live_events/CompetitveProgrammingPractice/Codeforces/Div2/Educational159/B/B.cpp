#include <iostream>
#include <string>
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

int t;

void subcase() {
    ll n, req, les, tas;
    cin >> n >> req >> les >> tas;

    ll l = 0, r = n;
    while (l < r) {
        ll mid = l + (r - l) / 2;
        ll cur = mid * les + min((n + 6) / 7, 2 * mid) * tas;
        if (cur >= req) r = mid;
        else l = mid + 1;
    }
    assert(l == r);

    cout << n - l << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
