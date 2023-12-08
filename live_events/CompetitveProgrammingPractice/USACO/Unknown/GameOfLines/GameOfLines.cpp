#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 200;

int n;
simps pts[N];
set<simps> ans;

simps getslope(simps a, simps b) {
    int x = a.first - b.first, y = a.second - b.second;

    if (x == 0) return {0, 1};
    if (y == 0) return {1, 0};

    if (x < 0) {
        x *= -1;
        y *= -1;
    }

    int g = gcd(x, abs(y));
    return {x / g, y / g};
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) ans.insert(getslope(pts[i], pts[j]));
    }
    cout << ans.size() << "\n";
	return 0;
}
