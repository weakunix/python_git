#include <iostream>
#include <cstdio>
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

int n, ans[N], below[N][N];
simps pts[N];

ll getcross(int a, int b, int c) {
    simps v1 = {pts[b].first - pts[a].first, pts[b].second - pts[a].second}, v2 = {pts[c].first - pts[a].first, pts[c].second - pts[a].second};
    return v1.first * v2.second - v1.second * v2.first;
}

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    memset(ans, 0, sizeof(ans));
    memset(below, 0, sizeof(below));

    cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    sort(pts, pts + n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = i + 1; k < j; k++) below[i][j] += (getcross(k, i, j) < 0);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (getcross(j, i, k) < 0) ans[below[i][k] - below[i][j] - below[j][k] - 1]++;
                else ans[below[i][j] + below[j][k] - below[i][k]]++;
                
            }
        }
    }

    for (int i = 0; i <= n - 3; i++) cout << ans[i] << "\n";
	return 0;
}
