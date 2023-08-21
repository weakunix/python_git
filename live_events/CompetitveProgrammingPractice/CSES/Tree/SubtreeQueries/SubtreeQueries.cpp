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

int n, q, cnt = 0;
vector<int> arr, st, en;
vector<ll> bit;
vector<vector<int>> adj;

void dfs(int node, int par) {
    cnt++;
    st[node] = cnt;
    for (int i : adj[node]) {
        if (i != par) dfs(i, node);
    }
    en[node] = cnt;
    return;
}

void set(int idx, int change) {
    for (; idx <= n; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll get(int idx) {
    ll res = 0;
    for (; idx > 0; idx ^= idx & (-idx)) res += bit[idx];
    return res;
}

int main() {
    cin >> n >> q;
    arr.resize(n);
    st.resize(n);
    en.resize(n);
    bit.resize(n + 1);
    adj.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0, -1);
    for (int i = 0; i < n; i++) set(st[i], arr[i]);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int s, x;
            cin >> s >> x;
            s--;
            set(st[s], x - arr[s]);
            arr[s] = x;
        }
        else {
            int s;
            cin >> s;
            s--;
            cout << get(en[s]) - get(st[s] - 1) << "\n";
        }
    }
	return 0;
}
