#include <iostream>
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

const int N = 1e5 + 1;

int n, x, pfx[N];
ll bit[2 * N], ans = 0;

void setbit(int idx, int change) {
    for (idx++; idx < 2 * N; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll getbit(int idx) {
    ll res = 0;
    for (idx++; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

int main() {
    pfx[0] = 1e5;
    memset(bit, 0, sizeof(bit));

    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        pfx[i] = pfx[i - 1] + (cur >= x ? 1 : -1);
    }


    for (int i = 0; i <= n; i++) {
        ans += getbit(pfx[i]);
        setbit(pfx[i], 1);
    }
    cout << ans << "\n";

	return 0;
}
