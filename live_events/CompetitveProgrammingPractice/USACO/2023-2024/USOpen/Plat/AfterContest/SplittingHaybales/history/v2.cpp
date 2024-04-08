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

const int N = 2e5 + 1, L = 18;

int n, q, arr[N];
ll pfx[N], alt[N];
vector<simps> nxt[L][N];

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

        if (idx <= n) {
            if (x <= 0) x += arr[idx];
            else x -= arr[idx];
            idx++;
        }

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

    if (idx <= n) {
        if (x <= 0) x += arr[idx];
        else x -= arr[idx];
        idx++;
    }

    return {idx, x};
}

simps& getnxt(int jmp, int idx, int x) {
    if (arr[idx - 2] == arr[idx - 1]) return nxt[jmp][idx][0];
    return nxt[jmp][idx][x + arr[idx - 2] - arr[idx - 1] - 1];
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

    for (int i = 3; i <= n; i++) {
        if (arr[i - 2] == arr[i - 1]) {
            for (int j = 0; j < L; j++) nxt[j][i].resize(1);
            getnxt(0, i, 0) = getjump(i, 0);
        }
        else {
            for (int j = 0; j < L; j++) nxt[j][i].resize(2 * (arr[i - 2] - arr[i - 1]));
            for (int j = -(arr[i - 2] - arr[i - 1]) + 1; j <= arr[i - 2] - arr[i - 1]; j++) getnxt(0, i, j) = getjump(i, j);
        }
    }

    for (int i = 1; i < L; i++) {
        for (int j = 3; j <= n; j++) {
            if (arr[j - 2] == arr[j - 1]) {
                simps cur = getnxt(i - 1, j, 0);
                if (cur.first <= n) cur = getnxt(i - 1, cur.first, cur.second);
                getnxt(i, j, 0) = cur;
            }
            else {
                for (int k = -(arr[j - 2] - arr[j - 1]) + 1; k <= arr[j - 2] - arr[j - 1]; k++) {
                    simps cur = getnxt(i - 1, j, k);
                    if (cur.first <= n) cur = getnxt(i - 1, cur.first, cur.second);
                    getnxt(i, j, k) = cur;
                }
            }
        }
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        
        simps cur = getjump(l, x);
        if (cur.first <= r + 1) {
            l = cur.first;
            x = cur.second;

            for (int j = L - 1; j >= 0; j--) {
                if (l > n) break;

                cur = getnxt(j, l, x);
                if (cur.first > r + 1) continue;
                l = cur.first;
                x = cur.second;
            }
        }

        if (l <= r) {
            if (x <= 0) {
                int lo = l, hi = r;
                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (x + pfx[mid] - pfx[l - 1] <= 0) lo = mid + 1;
                    else hi = mid;
                }
                assert(lo == hi);
                x += pfx[lo - 1] - pfx[l - 1];
                l = lo;
            }
            else {
                int lo = l, hi = r;
                while (lo < hi) {
                    int mid = lo + (hi - lo) / 2;
                    if (x - (pfx[mid] - pfx[l - 1]) > 0) lo = mid + 1;
                    else hi = mid;
                }
                assert(lo == hi);
                x -= pfx[lo - 1] - pfx[l - 1];
                l = lo;
            }

            if (x <= 0) x += abs(alt[r] - alt[l - 1]);
            else x -= abs(alt[r] - alt[l - 1]);
        }

        cout << x << "\n";
    }

	return 0;
}
