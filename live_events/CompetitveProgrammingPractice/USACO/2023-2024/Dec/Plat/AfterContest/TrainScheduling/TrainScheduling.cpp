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
ll t, arr[2][N], pfx[2][N], dp1[2][N][N], dp2[2][N], nxt[2][N];

struct Solve {
    ll getdp1(int s, int a, int b) {
        if (dp1[s][a][b] != 1e18) return dp1[s][a][b];

        ll curt = arr[s][a - 1] + t, curdel = 0;

        if (a == sz[s]) {
            for (int i = b; i < sz[1 - s] and arr[1 - s][i] < curt; i++) curdel += curt - arr[1 - s][i];
            setmn(dp1[s][a][b], curdel);
            return dp1[s][a][b];
        }

        setmn(dp1[s][a][b], getdp1(s, a + 1, b));

        curdel = curt * (nxt[s][a] - b) - (pfx[1 - s][nxt[s][a]] - pfx[1 - s][b]);
        
        setmn(dp1[s][a][b], getdp2(s, a, nxt[s][a]) + curdel);

        return dp1[s][a][b];
    }

    ll getdp2(int ss, int aa, int bb) {
        if (dp2[ss][aa] != 1e18) return dp2[ss][aa];

        int s = 1 - ss, a = bb, b = aa;
        ll curt = arr[ss][aa - 1] + t, curdel = 0;

        while (a < sz[s] and (arr[s][a] < curt or arr[1 - s][b] < curt + t)) {
            while (a < sz[s] and arr[s][a] < curt) {
                curdel += curt - arr[s][a];
                a++;
            }
            if (a == sz[s]) break;
            setmn(dp2[ss][aa], getdp1(s, a + 1, b) + curdel);
            s = 1 - s;
            swap(a, b);
            curt += t;
        }

        if (a == sz[s]) {
            s = 1 - s;
            swap(a, b);
            curt += t;
            for (; a < sz[s] and arr[s][a] < curt; a++) curdel += curt - arr[s][a];
            setmn(dp2[ss][aa], curdel);
            return dp2[ss][aa];
        }

        setmn(dp2[ss][aa], min(getdp1(s, a + 1, b), getdp1(1 - s, b + 1, a)) + curdel);

        return dp2[ss][aa];
    }
} ans;

int main() {
    for (int i = 0; i < N; i++) {
        fill(dp1[0][i], dp1[0][i] + N, 1e18);
        fill(dp1[1][i], dp1[1][i] + N, 1e18);
    }
    fill(dp2[0], dp2[0] + N, 1e18);
    fill(dp2[1], dp2[1] + N, 1e18);

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

    for (int i = 0; i < 2; i++) {
        pfx[i][0] = 0;
        for (int j = 1; j <= sz[i]; j++) pfx[i][j] = pfx[i][j - 1] + arr[i][j - 1];
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 1; j <= sz[i]; j++) {
            nxt[i][j] = 0;
            while (nxt[i][j] < sz[1 - i] and arr[1 - i][nxt[i][j]] < arr[i][j - 1] + t) nxt[i][j]++;
        }
    }

    cout << min(ans.getdp1(0, 1, 0), ans.getdp1(1, 1, 0)) << "\n";

	return 0;
}
