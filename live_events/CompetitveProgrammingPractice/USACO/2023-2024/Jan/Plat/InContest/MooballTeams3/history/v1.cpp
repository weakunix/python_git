#include <iostream>
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

const int N = 3001, modval = 1e9 + 7; //TODO SUBTASK 3

int n, pfx[2][N][N];
ll pw[N], ans = 0;

int main() {
    clr(pfx, 0);
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = 2 * pw[i - 1] % modval;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pfx[0][x][y]++;
        pfx[1][n - y + 1][x]++;
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) for (int k = 0; k < 2; k++) pfx[k][i][j] += pfx[k][i - 1][j] + pfx[k][i][j - 1] - pfx[k][i - 1][j - 1];

    for (int k = 0; k < 2; k++) {
        for (int i = 1; i <= n; i++) {
            int cur = pfx[k][i][n] - pfx[k][i - 1][n];
            ans = (ans + (pw[cur] - 1) * pw[pfx[k][i - 1][n]] % modval * (pw[n - pfx[k][i][n]] - 1) % modval) % modval;
        }


        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int tp = pfx[k][j][i] - pfx[k][j][i - 1], rt = pfx[k][j][i] - pfx[k][j - 1][i];
                bool corner = pfx[k][j][i] - pfx[k][j][i - 1] - pfx[k][j - 1][i] + pfx[k][j - 1][i - 1];
                ll cur = 0;
                if (corner) {
                    cur = (pw[tp - 1] - 1) * (pw[rt - 1] - 1) % modval;
                    cur = (cur + pw[tp - 1] * pw[rt - 1] % modval) % modval;
                    cur = cur * pw[pfx[k][j][i] - tp - rt + 1] % modval;
                }
                else cur = (pw[tp] - 1) * (pw[rt] - 1) % modval * pw[pfx[k][j][i] - tp - rt] % modval;
                cur = cur * (pw[n - pfx[k][n][i] - pfx[k][j][n] + pfx[k][j][i]] - 1) % modval;
                ans = (ans + modval - cur) % modval;
            }
        }
    }

    cout << 2 * ans % modval << "\n";

	return 0;
}
