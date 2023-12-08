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

const int N = 1e5 + 1;

int n, a1[N], a2[N];
ll bit[N];

void setbit(int idx, int change) {
    for (; idx <= n; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll getbit(int idx) {
    ll res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

ll calc(int (&still)[N], int (&move)[N]) {
    memset(bit, 0, sizeof(bit));

    int idx[N], arr[N];
    ll cur = 0, ans;
    for (int i = 1; i <= n; i++) idx[still[i]] = i;
    for (int i = 1; i <= n; i++) arr[i] = idx[move[i]];
    
    for (int i = 1; i <= n; i++) {
        cur += getbit(n) - getbit(arr[i]);
        setbit(arr[i], 1);
    }
    ans = cur;
    for (int i = 1; i <= n; i++) {
        cur += n - arr[i] - arr[i] + 1;
        ans = min(cur, ans);
    }
    return ans;
}

int main() {
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a1[i];
    for (int i = 1; i <= n; i++) cin >> a2[i];

    cout << min(calc(a1, a2), calc(a2, a1)) << "\n";
	return 0;
}
