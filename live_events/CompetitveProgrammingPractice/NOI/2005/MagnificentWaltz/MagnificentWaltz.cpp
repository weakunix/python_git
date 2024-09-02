#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 200, M = 200, K = 201;
int n, m, k, stx, sty, dp[K][N][M];
bool grid[N][M];
simps q[K];

int main() {
    clr(dp, 0);
 
    cin >> n >> m >> stx >> sty >> k;
    stx--; sty--;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            grid[i][j] = (c == 'x');
        }
    }
    for (int i = 0; i < k; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        q[i] = {b - a + 1, d - 1};
    }

    for (int i = k - 1; i >= 0; i--) {
        int mx = q[i].first, d = q[i].second;

        if (d == 0) {
            for (int j = 0; j < m; j++) {
                priority_queue<simps> pq;
                for (int l = 0; l < n; l++) {
                    if (grid[l][j]) {
                        while (pq.size()) pq.pop();
                        continue;
                    }
                    pq.push({dp[i + 1][l][j] - l, l});
                    while (pq.size()) {
                        int cur = pq.top().second;
                        if (cur < l - mx) {
                            pq.pop();
                            continue;
                        }
                        dp[i][l][j] = dp[i + 1][cur][j] + l - cur;
                        break;
                    }
                }
            }
        }
        
        else if (d == 1) {
            for (int j = 0; j < m; j++) {
                priority_queue<simps> pq;
                for (int l = n - 1; l >= 0; l--) {
                    if (grid[l][j]) {
                        while (pq.size()) pq.pop();
                        continue;
                    }
                    pq.push({dp[i + 1][l][j] + l, l});
                    while (pq.size()) {
                        int cur = pq.top().second;
                        if (cur > l + mx) {
                            pq.pop();
                            continue;
                        }
                        dp[i][l][j] = dp[i + 1][cur][j] + cur - l;
                        break;
                    }
                }
            }
        }

        else if (d == 2) {
            for (int j = 0; j < n; j++) {
                priority_queue<simps> pq;
                for (int l = 0; l < m; l++) {
                    if (grid[j][l]) {
                        while(pq.size()) pq.pop();
                        continue;
                    }
                    pq.push({dp[i + 1][j][l] - l, l});
                    while (pq.size()) {
                        int cur = pq.top().second;
                        if (cur < l - mx) {
                            pq.pop();
                            continue;
                        }
                        dp[i][j][l] = dp[i + 1][j][cur] + l - cur;
                        break;
                    }
                }
            }
        }

        else {
            for (int j = 0; j < n; j++) {
                priority_queue<simps> pq;
                for (int l = m - 1; l >= 0; l--) {
                    if (grid[j][l]) {
                        while (pq.size()) pq.pop();
                        continue;
                    }
                    pq.push({dp[i + 1][j][l] + l, l});
                    while (pq.size()) {
                        int cur = pq.top().second;
                        if (cur > l + mx) {
                            pq.pop();
                            continue;
                        }
                        dp[i][j][l] = dp[i + 1][j][cur] + cur - l;
                        break;
                    }
                }
            }
        }
    }

    cout << dp[0][stx][sty] << "\n";

	return 0;
}
