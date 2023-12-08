#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 1e5, M = 1e6;

int n, curidx = 0;
ll bit1[M], bit2[M], ans = N;
simps arr[N];

void setbit(ll (&bit)[M], int idx, int change) {
    for (; idx < M; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll getbit(ll (&bit)[M], int idx) {
    ll res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

void calc() {
    int b = 1, t = M - 1;
    while (b <= t) {
        int mid = b + (t - b) / 2;
        ll tl = getbit(bit1, M - 1) - getbit(bit1, mid), bl = getbit(bit1, mid), tr = getbit(bit2, M - 1) - getbit(bit2, mid), br = getbit(bit2, mid);
        ans = min(max({tl, bl, tr, br}), ans);
        if (tl >= bl and tr >= br) {
            b = mid + 1;
            continue;
        }
        if (bl >= tl and br >= tr) {
            t = mid - 1;
            continue;
        }
        if (tl > bl) {
            assert(tr < br);
            if (tl > br) b = mid + 1;
            else t = mid - 1;
        }
        else {
            assert(tr > br);
            if (bl > tr) t = mid - 1;
            else b = mid + 1;
        }
    }
    return;
}

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    memset(bit1, 0, sizeof(bit1));
    memset(bit2, 0, sizeof(bit2));

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
        setbit(bit2, arr[i].second, 1);
    }

    sort(arr, arr + n);

    calc();
    while (curidx < n) {
        int cur = arr[curidx].first;
        while (curidx < n and arr[curidx].first == cur) {
            setbit(bit2, arr[curidx].second, -1);
            setbit(bit1, arr[curidx].second, 1);
            curidx++;
        }
        calc();
    }
    
    cout << ans << "\n";

	return 0;
}
