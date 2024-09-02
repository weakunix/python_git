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
#include <chrono>
#include <random>

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

mt19937 rnd((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5, D = 100, T = 10;

int n, d, k, arr[N][D], sdot[N], randmul[N], randsm;

int solve2() {
    int mul[D];

    for (int i = 0; i < d; i++) {
        mul[i] = 0;
        for (int j = 0; j < n; j++) mul[i] = (mul[i] + arr[j][i] * randmul[j]) % k;
    }

    for (int i = 0; i < n; i++) {
        int a = 0;
        for (int j = 0; j < d; j++) a = (a + arr[i][j] * mul[j]) % k;

        int b = ((randsm + randmul[i] * (sdot[i] - 1)) % k + k) % k;

        if (a != b) return i;
    }

    return -1;
}

int solve3() {
    int g[D][D];

    for (int u = 0; u < d; u++) {
        for (int v = 0; v < d; v++) {
            g[u][v] = 0;
            for (int i = 0; i < n; i++) g[u][v] = (g[u][v] + randmul[i] * arr[i][u] * arr[i][v]) % 3;
        }
    }

    for (int x = 0; x < n; x++) {
        int a = 0;
        for (int u = 0; u < d; u++) for (int v = 0; v < d; v++) a = (a + arr[x][u] * arr[x][v] * g[u][v]) % 3;
        
        int b = ((randsm + randmul[x] * (sdot[x] * sdot[x] - 1)) % 3 + 3) % 3;

        if (a % 3 != b) return x;
    }

    return -1;
}

int main() {
    cin >> n >> d >> k;
    for (int i = 0; i < n; i++) {
        sdot[i] = 0;
        for (int j = 0; j < d; j++) {
            cin >> arr[i][j];
            arr[i][j] %= k;
            sdot[i] = (sdot[i] + arr[i][j] * arr[i][j]) % k;
        }
    }

    for (int i = 0; i < T; i++) {
        randsm = 0;
        for (int i = 0; i < n; i++) {
            randmul[i] = rnd() % 2;
            randsm += randmul[i];
        }

        int res = (k == 2 ? solve2() : solve3());
        if (res == -1) continue;

        for (int j = 0; j < n; j++) {
            if (j == res) continue;
            int cur = 0;
            for (int l = 0; l < d; l++) cur = (cur + arr[res][l] * arr[j][l]) % k;
            if (cur == 0) {
                cout << min(res, j) + 1 << " " << max(res, j) + 1 << "\n";
                return 0;
            }
        }
        assert(false);
    }

    cout << "-1 -1\n";

	return 0;
}
