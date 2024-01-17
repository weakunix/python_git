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

ll findmst(int msk) {
    ll cnt = 0, res = 0;

    for (int i = 0; i < n; i++) {
        if (not (msk & (1 << i))) continue;

        cnt++;

        priority_queue<simps, vector<simps>, greater<simps>> pq;
        pq.push({0, i});

        while (pq.size()) {
            ll node = pq.top().second, dist = pq.top().first;
            pq.pop();

            if (not (msk & (1 << node))) continue;
            msk ^= 1 << node;
            res += dist;

            for (simps& s : adj[node]) {
                if (not (msk & (1 << s.first))) continue;
                pq.push({s.second, s.first});
            }
        }
    }

    return res + (cnt - 1) * MX;
}

int main() {
    //freopen("acquire.in", "r", stdin);
    //freopen("acquire.out", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    dp[(1 << n) - 1] = findmst((1 << n) - 1);
    for (int i = (1 << n) - 2; i > 0; i--) {
        dp[i] = findmst(i);
        for (int j = 0; j < n; j++) if (not (i & (1 << j))) setmn(dp[i], dp[i | (1 << j)]);
    }

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
