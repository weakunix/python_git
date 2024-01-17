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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a);
    return;
}

const int N = 5001;

int n, sz[2] = {0, 0};
ll t, arr[2][N], ans = 1e18, dp[2][N][N];

ll getdp(int ss, int aa, int bb) {
    int s = ss, a = aa, b = bb;

    if (dp[ss][aa][bb] != 1e18) return dp[ss][aa][bb];

    ll curt = arr[s][a - 1], curdel = 0;

    while (a < sz[s] and (arr[s][a] < curt or arr[1 - s][b] < curt + t)) {
        while (a < sz[s] and arr[s][a] < curt) {
            curdel += curt - arr[s][a];
            a++;
        }
        if (a == sz[s]) break;
        setmn(dp[ss][aa][bb], getdp(s, a + 1, b) + curdel);
        s = 1 - s;
        swap(a, b);
        curt += t;
    }

    if (a == sz[s]) {
        s = 1 - s;
        swap(a, b);
        curt += t;
        for (; a < sz[s] and arr[s][a] < curt; a++) curdel += curt - arr[s][a];
        setmn(dp[ss][aa][bb], curdel);
    }
    else setmn(dp[ss][aa][bb], min(getdp(s, a + 1, b), getdp(1 - s, b + 1, a)) + curdel);

    return dp[ss][aa][bb];
}

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

    cout << min(getdp(0, 1, 0), getdp(1, 1, 0)) << "\n";

	return 0;
}
