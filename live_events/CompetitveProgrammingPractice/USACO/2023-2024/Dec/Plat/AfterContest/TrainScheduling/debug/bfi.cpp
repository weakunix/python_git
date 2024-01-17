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

const int N = 5001;

int n, sz[2] = {0, 0};
ll t, arr[2][N], ans = 1e18, dp[2][N][N];

int main() {
    for (int i = 0; i < N; i++) {
        fill(dp[0][i], dp[0][i] + N, 1e18);
        fill(dp[1][i], dp[1][i] + N, 1e18);
    }

    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        int cur;
        char c;
        ll k;
        cin >> c >> k;
        cur = (c == 'A' ? 0 : 1);
        arr[cur][sz[cur]] = k;
        sz[cur]++;
    }

    if (not sz[0] or not sz[1]) {
        cout << "0\n";
        return 0;
    }

    sort(arr[0], arr[0] + sz[0]);
    sort(arr[1], arr[1] + sz[1]);

    dp[0][1][0] = 0;
    dp[1][1][0] = 0;

    for (int i = 0; i <= sz[0]; i++) {
        for (int j = 0; j <= sz[1]; j++) {
            for (int k = 0; k < 2; k++) {

                int s = k, a = i, b = j, works = 0;
                if (k) swap(a, b);

                ll curt = arr[s][a - 1], del = dp[s][a][b];
                if (del == 1e18) continue;

                //cout << s << " " << a << " " << b << " " << del << "\n";

                while (works < 2 and a < sz[s]) {
                    while (a < sz[s] and curt > arr[s][a]) {
                        del += curt - arr[s][a];
                        a++;
                        works = 0;
                    }
                    if (a == sz[s]) break;
                    dp[s][a + 1][b] = min(del, dp[s][a + 1][b]);
                    
                    s = 1 - s;
                    swap(a, b);
                    curt += t;
                    works++;
                }

                if (works < 2) {
                    s = 1 - s;
                    swap(a, b);
                    curt += t;
                    for (int l = a; l < sz[s] and arr[s][l] < curt; l++) del += curt - arr[s][l];

                    ans = min(del, ans);
                }
            }
        }
    }

    cout << ans << "\n";

	return 0;
}
