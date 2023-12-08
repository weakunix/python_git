#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2e5 + 1;

int t;

void subcase() {
    int n;
    ll c, arr[N];
    vector<simps> req;
    cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (i == 1) continue;
        req.push_back({c * i - arr[i], i});
    }
    sort(rall(req));

    while (req.size()) {
        ll curreq = req.back().first, cur = req.back().second;
        req.pop_back();
        if (curreq > arr[1]) {
            cout << "NO\n";
            return;
        }
        arr[1] += arr[cur];
    }

    cout << "YES\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
