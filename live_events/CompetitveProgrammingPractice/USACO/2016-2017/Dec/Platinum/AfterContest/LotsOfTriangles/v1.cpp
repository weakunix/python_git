#include <iostream>
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

const int N = 300;

int n, ans[N];
simps pts[N];

ll getcross(int a, int b, int c) {
    simps v1 = {pts[b].first - pts[a].first, pts[b].second - pts[a].second}, v2 = {pts[c].first - pts[a].first, pts[c].second - pts[a].second};
    return v1.first * v2.second - v1.second * v2.first;
}

int main() {
    memset(ans, 0, sizeof(ans));

    cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    sort(pts, pts + n);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int cur = 0;
                for (int l = i + 1; l < k; l++) {
                    ll a = getcross(l, i, j), b = getcross(l, j, k), c = getcross(l, k, i), mn = min({a, b, c}), mx = max({a, b, c});
                    cur += (mx < 0 or mn > 0);
                }
                ans[cur]++;
            }
        }
    }

    for (int i = 0; i <= n - 3; i++) cout << ans[i] << "\n";
	return 0;
}
