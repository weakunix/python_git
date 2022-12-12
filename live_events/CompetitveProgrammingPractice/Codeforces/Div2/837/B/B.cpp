#include <iostream>
#include <string>
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

void subcase() {
    int n, m, l = 0, r = 0;
    ll ans = 1;
    vector<set<int>> notfriend;
    cin >> n >> m;
    notfriend.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        notfriend[a].insert(b);
        notfriend[b].insert(a);
    }
    while (r < n - 1) {
        r++;
        auto it = notfriend[r].lower_bound(l);
        while (it != notfriend[r].end() and *it < r) {
            l++;
            it = notfriend[r].lower_bound(l);
        }
        ans += r - l + 1;
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
