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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 301;

int n, k;
ll w[N][N];

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> w[i][j];

    for (int i = 0; i < n * n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        w[u][v] = -1;
        
        ll cur[N], nxt[N];
        clr(cur, -1);
        cur[0] = 0;

        for (int j = 0; j < k; j++) {
            clr(nxt, -1);
            for (int l = 0; l < n; l++) {
                if (cur[l] == -1) continue;
                for (int o = 0; o < n; o++) {
                    if (w[l][o] == -1) continue;
                    ll res = cur[l] + w[l][o];
                    if (nxt[o] == -1 or nxt[o] > res) nxt[o] = res;
                }
            }
            memmove(cur, nxt, sizeof(nxt));
        }

        cout << cur[n - 1] << "\n";
    }

	return 0;
}
