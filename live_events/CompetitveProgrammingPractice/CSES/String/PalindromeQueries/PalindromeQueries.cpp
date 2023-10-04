#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<simps, simps> foursome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2e5 + 1, B = 41, mod1 = 1e9 + 7, mod2 = 1e9 + 9;

int n, m;
ll pw1[N], pw2[N], forseg1[4 * N], forseg2[4 * N], backseg1[4 * N], backseg2[4 * N];

void set(int node, int l, int r, int idx, int val) {
    if (idx > r or idx < l) return;
    if (l == r) {
        forseg1[node] = val;
        forseg2[node] = val;
        backseg1[node] = val;
        backseg2[node] = val;
        return;
    }
    int mid = l + (r - l) / 2, h1 = mid - l + 1, h2 = r - mid;
    set(2 * node, l, mid, idx, val);
    set(2 * node + 1, mid + 1, r, idx, val);
    forseg1[node] = (pw1[h2] * forseg1[2 * node] % mod1 + forseg1[2 * node + 1]) % mod1;
    forseg2[node] = (pw2[h2] * forseg2[2 * node] % mod2 + forseg2[2 * node + 1]) % mod2;
    backseg1[node] = (backseg1[2 * node] + pw1[h1] * backseg1[2 * node + 1] % mod1) % mod1;
    backseg2[node] = (backseg2[2 * node] + pw2[h1] * backseg2[2 * node + 1] % mod2) % mod2;
    return;
}

void get(int node, int l, int r, int a, int b, ll& ansf1, ll& ansf2, ll& ansb1, ll& ansb2) {
    if (a > r or b < l) return;
    if (l >= a and r <= b) {
        int lb = l - a, rb = b - r;
        ansf1 = (ansf1 + forseg1[node] * pw1[rb] % mod1) % mod1;
        ansf2 = (ansf2 + forseg2[node] * pw2[rb] % mod2) % mod2;
        ansb1 = (ansb1 + backseg1[node] * pw1[lb] % mod1) % mod1;
        ansb2 = (ansb2 + backseg2[node] * pw2[lb] % mod2) % mod2;
        return;
    }
    int mid = l + (r - l) / 2;
    get(2 * node, l, mid, a, b, ansf1, ansf2, ansb1, ansb2);
    get(2 * node + 1, mid + 1, r, a, b, ansf1, ansf2, ansb1, ansb2);
    return;
}

int main() {
    memset(forseg1, 0, sizeof(forseg1));
    memset(forseg2, 0, sizeof(forseg2));
    memset(backseg1, 0, sizeof(backseg1));
    memset(backseg2, 0, sizeof(backseg2));
    pw1[0] = 1; pw2[0] = 1;
    for (int i = 1; i < N; i++) {
        pw1[i] = pw1[i - 1] * B % mod1;
        pw2[i] = pw2[i - 1] * B % mod2;
    }

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        set(1, 0, n - 1, i, (c - 'a') + 1);
    }

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            char x;
            cin >> k >> x;
            set(1, 0, n - 1, k - 1, (x - 'a') + 1);
        }
        else {
            ll ansf1 = 0, ansf2 = 0, ansb1 = 0, ansb2 = 0;
            int a, b;
            cin >> a >> b;
            get(1, 0, n - 1, a - 1, b - 1, ansf1, ansf2, ansb1, ansb2);
            cout << (ansf1 == ansb1 and ansf2 == ansb2 ? "YES\n" : "NO\n");
        }
    }
	return 0;
}
