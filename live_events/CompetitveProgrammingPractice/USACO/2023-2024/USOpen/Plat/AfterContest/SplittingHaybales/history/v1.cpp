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

const int N = 2e5 + 1;

int n, q, arr[N];
ll pfx[N], alt[N];

simps getjump(int idx, int x) {
    if (x <= 0) {
        if (x + pfx[n] - pfx[idx - 1] <= 0) return {n + 1, x + pfx[n] - pfx[idx - 1]};

        int l = idx, r = n;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (x + pfx[mid] - pfx[idx - 1] <= 0) l = mid + 1;
            else r = mid;
        }
        assert(l == r);
        x += pfx[l - 1] - pfx[idx - 1];
        idx = l;

        l = idx;
        r = n;
        while (l < r) {
            int mid = l + (r - l + 1) / 2;
            ll cur = abs(alt[mid] - alt[idx - 1]), prv = abs(alt[mid - 1] - alt[idx - 1]);
            if ((mid - idx) % 2 == 0) {
                if (x + cur > 0 and x + prv <= 0) l = mid;
                else r = mid - 1;
            }
            else {
                if (x + cur <= 0 and x + prv > 0) l = mid;
                else r = mid - 1;
            }
        }
        assert(l == r);
        x += abs(alt[l] - alt[idx - 1]);
        idx = l + 1;

        return {idx, x};
    }

    if (x - (pfx[n] - pfx[idx - 1]) > 0) return {n + 1, x - (pfx[n] - pfx[idx - 1])};

    int l = idx, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (x - (pfx[mid] - pfx[idx - 1]) > 0) l = mid + 1;
        else r = mid;
    }
    assert(l == r);
    x -= pfx[l - 1] - pfx[idx - 1];
    idx = l;

    l = idx;
    r = n;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        ll cur = abs(alt[mid] - alt[idx - 1]), prv = abs(alt[mid - 1] - alt[idx - 1]);
        if ((mid - idx) % 2 == 0) {
            if (x - cur <= 0 and x - prv > 0) l = mid;
            else r = mid - 1;
        }
        else {
            if (x - cur > 0 and x - prv <= 0) l = mid;
            else r = mid - 1;
        }
    }
    assert(l == r);
    x -= abs(alt[l] - alt[idx - 1]);
    idx = l + 1;

    return {idx, x};
}

int main() {
    pfx[0] = 0;
    alt[0] = 0;

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pfx[i] = pfx[i - 1] + arr[i];
        alt[i] = alt[i - 1] + arr[i] * (i % 2 ? 1 : -1);
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;

        simps cur = getjump(l, x);
        while (cur.first <= r + 1) {
            l = cur.first;
            x = cur.second;
            if (l > r) break;
            cur = getjump(l, x);
        }

        for (int j = l; j <= r; j++) {
            if (x <= 0) x += arr[j];
            else x -= arr[j];
        }

        cout << x << "\n";
    }

	return 0;
}
