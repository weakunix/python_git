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

const int N = 1e5, M = 1e6 + 1;

int n, l, c, mx, arr[N], frac[N];
ll bit[M], sm = 0, ans = 0;

void setbit(int idx, int change) {
    for (idx++; idx < M; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll getbit(int idx) {
    ll res = 0;
    for (idx++; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

int main() {
    cin >> n >> l >> c;
    for (int i = 0; i < n; i++) cin >> arr[i];
    sort(arr, arr + n);
    mx = arr[n - 1];
    
    for (int i = 0; i < n; i++) {
        frac[i] = (ll) l * arr[i] % mx;
        arr[i] = (ll) l * arr[i] / mx;
    }
    for (int i = 0; i < n; i++) {
        ans += (ll) i * arr[i] - sm - getbit(M - 2) + getbit(frac[i]);
        setbit(frac[i], 1);
        sm += arr[i];
    }
    cout << ans << "\n";
	return 0;
}
