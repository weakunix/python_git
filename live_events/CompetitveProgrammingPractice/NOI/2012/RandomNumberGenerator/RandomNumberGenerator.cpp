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

const int L = 61;

ll m, a, c, x, n, g;
__int128 pw[L], f[L];

int main() {
    cin >> m >> a >> c >> x >> n >> g;

    pw[0] = 1;
    pw[1] = a;
    for (int i = 2; i < L; i++) pw[i] = pw[i - 1] * pw[i - 1] % m;

    f[0] = 1;
    for (int i = 1; i < L; i++) f[i] = (f[i - 1] * pw[i] % m + f[i - 1]) % m;

    __int128 A = 1, B = 0;

    int cnt = 1;
    while (n) {
        if (n & 1) {
            A = A * pw[cnt] % m;
            B = (B * pw[cnt] % m + f[cnt - 1]) % m;
        }
        n >>= 1;
        cnt++;
    }

    ll res = (A * x % m + B * c % m) % m;

    cout << res % g << "\n";

	return 0;
}
