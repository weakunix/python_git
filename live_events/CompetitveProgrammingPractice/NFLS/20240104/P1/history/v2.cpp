#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 21, S = 1 << 21, MX = 2147483647;

int n, m, q;
vector<simps> adj[N];
ll dp[S];

ll genmst(int tarmsk) {
    int curmsk = 0;
    ll cnt = 0, res = 0;

    for (int i = 0; i < n; i++) {
        if (not (tarmsk & (1 << i))) continue;

        cnt++;

        priority_queue<simps, vector<simps>, greater<simps>> pq;
        pq.push({0, i});

        while (pq.size()) {
            ll node = pq.top().second, dist = pq.top().first;
            pq.pop();

            if (not (tarmsk & (1 << node))) continue;
            tarmsk ^= 1 << node;
            curmsk |= 1 << node;
            res += dist;
            dp[curmsk] = res + (cnt - 1) * MX;

            for (simps& s : adj[node]) {
                if (not (tarmsk & (1 << s.first))) continue;
                pq.push({s.second, s.first});
            }
        }
    }

    return res + (cnt - 1) * MX;
}

int main() {
    //freopen("acquire.in", "r", stdin);
    //freopen("acquire.out", "w", stdout);

    memset(dp, -1, sizeof(dp));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    for (int i = (1 << n) - 1; i > 0; i--) if (dp[i] == -1) genmst(i);

    for (int i = (1 << n) - 2; i > 0; i--) for (int j = 0; j < n; j++) if (not (i & (1 << j))) setmn(dp[i], dp[i | (1 << j)]);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int k, msk = 0;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int cur;
            cin >> cur;
            cur--;
            msk |= 1 << cur;
        }
        cout << dp[msk] << "\n";
    }

	return 0;
}
