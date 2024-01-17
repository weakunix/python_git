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
typedef pair<ll, ll> simps;
typedef pair<ll, simps> threesome;

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

int n, m, q, idx[S], seen[N], unseen[N], curidx = 0, opcnt = 0;
ll dp[S], adj[N][N];

int main() {
    //freopen("acquire.in", "r", stdin);
    //freopen("acquire.out", "w", stdout);
    
    fill(dp, dp + S, 1e18);
    for (int i = 0; i < N; i++) fill(adj[i], adj[i] + N, MX);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a][b] = c;
        adj[b][a] = c;
    }

    for (int i = 1; i < (1 << n); i++) {
        if ((i & (-i)) == i) dp[i] = 0;

        int idxs = 0, idxu = 0;
        for (int j = 0; j < n; j++) {
            opcnt++; //TODO DEBUG
            if (i & (1 << j)) {
                seen[idxs] = j;
                idxs++;
            }
            else {
                unseen[idxu] = j;
                idxu++;
            }
        }
        
        for (int j = 0; j < idxu; j++) {
            int nxt = i | (1 << unseen[j]);
            for (int k = 0; k < idxs; k++) {
                setmn(dp[nxt], dp[i] + adj[unseen[j]][seen[k]]);
                opcnt++; //TODO DEBUG
            }
        }
    }

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

    cout << endl << opcnt << endl;

	return 0;
}
