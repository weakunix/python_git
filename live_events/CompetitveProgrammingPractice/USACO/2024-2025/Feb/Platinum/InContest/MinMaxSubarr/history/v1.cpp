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

const int N = 1e6;

int n, a[N];
ll ans = 0;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    //1
    for (int i = 0; i < n; i++) ans += a[i];

    //2
    for (int i = 0; i < n - 1; i++) ans += min(a[i], a[i + 1]);

    //3
    for (int i = 0; i < n - 2; i++) ans += max(a[i], a[i + 2]);

    //4
    for (int i = 0; i < n - 3; i++) {
        int best1 = -1, best2 = -1, best3 = -1;
        for (int j = i; j < i + 4; j++) {
            setmx(best3, a[j]);
            if (best3 > best2) swap(best2, best3);
            if (best2 > best1) swap(best1, best2);
        }

        int l = -1, r = -1;
        for (int j = 0; j < 4; j++) {
            if (l == -1 and a[i + j] == best1) l = j;
            else if (r == -1 and a[i + j] == best2) r = j;
        }
        if (l > r) swap(l, r);

        if (l == 0 and r == 2) ans += best3;
        else if (l == 1 and r == 2) ans += best3;
        else if (l == 1 and r == 3) ans += best3;
        else ans += best2;
    }
    
    //6
    for (int i = 0; i < n - 5; i++) {
        int best1 = -1, best2 = -1, best3 = -1;
        for (int j = i; j < i + 6; j++) {
            setmx(best3, a[j]);
            if (best3 > best2) swap(best2, best3);
            if (best2 > best1) swap(best1, best2);
        }

        int l = -1, r = -1;
        for (int j = 0; j < 6; j++) {
            if (l == -1 and a[i + j] == best1) l = j;
            else if (r == -1 and a[i + j] == best2) r = j;
        }
        if (l > r) swap(l, r);

        if (l == 1 and r == 3) ans += best3;
        else if (l == 1 and r == 4) ans += best3;
        else if (l == 2 and r == 4) ans += best3;
        else ans += best2;
    }

    //5, 7 to n //FIXME
    for (int l = 0; l < n; l++) {
        int best1 = -1, best2 = -1;
        for (int r = l, len = 1; r < n; r++, len++) {
            setmx(best2, a[r]);
            if (best2 > best1) swap(best1, best2);

            if (len < 7 and len != 5) continue;

            if (len % 2 == 1) ans += best1;
            else ans += best2;
        }
    }

    cout << ans << "\n";

	return 0;
}
