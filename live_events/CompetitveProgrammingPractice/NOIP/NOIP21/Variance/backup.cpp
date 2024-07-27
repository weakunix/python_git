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

const int N = 1e4, M = 5e5 + 1;

int n, arr[N], diff[N], dp[2][M], vis[2][M];
ll ans = 1e18;
queue<int> psbl;

int main() {
    clr(vis, -1);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (i) diff[i] = arr[i] - arr[i - 1];
    }

    sort(diff + 1, diff + n);

    dp[0][0] = 0;
    psbl.push(0);

    for (int i = 0; i < n - 1; i++) {
        int curcnt = psbl.size();

        for (int j = 0; j < curcnt; j++) {
            int s = psbl.front(), curdp = dp[i % 2][s];
            psbl.pop();
            
            int nxts = s + (i + 1) * diff[i + 1], nxtdp = curdp + 2 * diff[i + 1] * s + (i + 1) * diff[i + 1] * diff[i + 1];
            if (vis[(i + 1) % 2][nxts] < i + 1) {
                vis[(i + 1) % 2][nxts] = i + 1;
                psbl.push(nxts);
                dp[(i + 1) % 2][nxts] = nxtdp;
            }
            else setmn(dp[(i + 1) % 2][nxts], nxtdp);

            nxts = s + s + diff[i + 1];
            nxtdp = curdp + (s + diff[i + 1]) * (s + diff[i + 1]);
            if (vis[(i + 1) % 2][nxts] < i + 1) {
                vis[(i + 1) % 2][nxts] = i + 1;
                psbl.push(nxts);
                dp[(i + 1) % 2][nxts] = nxtdp;
            }
            else setmn(dp[(i + 1) % 2][nxts], nxtdp);
        }
    }
    
    while (psbl.size()) {
        ll s = psbl.front(), curdp = dp[(n - 1) % 2][s];
        psbl.pop();
        setmn(ans, n * curdp - s * s);
    }

    cout << ans << "\n";

	return 0;
}
