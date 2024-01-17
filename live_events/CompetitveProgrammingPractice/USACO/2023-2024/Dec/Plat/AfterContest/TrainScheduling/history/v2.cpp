#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
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

const int N = 2001; //BFI O(N^4)

int n, a = 0, b = 0;
ll t, arra[N], arrb[N], ans = 1e18;
unordered_map<ll, ll> dp1[N][N], dp2[N][N];

int main() {
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        char c;
        ll k;
        cin >> c >> k;
        if (c == 'A') {
            arra[a] = k;
            a++;
        }
        else {
            arrb[b] = k;
            b++;
        }
    }

    sort(arra, arra + a);
    sort(arrb, arrb + b);

    dp1[0][0][0] = 0;
    dp2[0][0][0] = 0;

    for (int i = 0; i <= a; i++) {
        for (int j = 0; j <= b; j++) {
            if (i > 0) {
                for (auto& u : dp1[i - 1][j]) {
                    ll cur = max(u.first, arra[i - 1]);
                    if (not dp1[i][j].count(cur)) dp1[i][j][cur] = 1e18;
                    dp1[i][j][cur] = min(u.second + max(cur - arra[i - 1], (ll) 0), dp1[i][j][cur]);

                    if (not dp2[i][j].count(cur + t)) dp2[i][j][cur + t] = 1e18;
                    dp2[i][j][cur + t] = min(u.second + max(cur - arra[i - 1], (ll) 0), dp2[i][j][cur + t]);
                }
            }
            if (j > 0) {
                for (auto& u : dp2[i][j - 1]) {
                    ll cur = max(u.first, arrb[j - 1]);
                    if (not dp2[i][j].count(cur)) dp2[i][j][cur] = 1e18;
                    dp2[i][j][cur] = min(u.second + max(cur - arrb[j - 1], (ll) 0), dp2[i][j][cur]);

                    if (not dp1[i][j].count(cur + t)) dp1[i][j][cur + t] = 1e18;
                    dp1[i][j][cur + t] = min(u.second + max(cur - arrb[j - 1], (ll) 0), dp1[i][j][cur + t]);
                }
            }
        }
    }

    for (auto& u : dp1[a][b]) ans = min(u.second, ans);
    for (auto& u : dp2[a][b]) ans = min(u.second, ans);

    cout << ans << "\n";

	return 0;
}
