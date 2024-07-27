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
typedef pair<ll, ll> simps;
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

const int N = 18, S = 1 << N, modval = 998244353;

int n, m, subsz[S], vis[S];
ll distu[S], subsm[S], ans = 0;
map<int, ll> edge[S], distd[S];

int main() {
    clr(vis, 0);

    cin >> n >> m;
    for (int i = 2; i < (1 << n); i++) cin >> distu[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        if (edge[a][b]) setmn(edge[a][b], c);
        else edge[a][b] = c;
    }

    for (int i = 1; i < (1 << n); i++) {
        queue<int> q;
        priority_queue<simps, vector<simps>, greater<simps>> pq;

        q.push(2 * i);
        q.push(2 * i + 1);
        while (q.front() < (1 << n)) {
            int node = q.front();
            q.pop();

            distd[i][node] = (edge[i][node] ? edge[i][node] : 1e18);
            if (i > 1) setmn(distd[i][node], distd[i / 2][node] + distu[i]);
            pq.push({distd[i][node], node});

            q.push(2 * node);
            q.push(2 * node + 1);
        }

        while (not pq.empty()) {
            int node = pq.top().second;
            ll curd = pq.top().first;
            pq.pop();

            if (vis[node] == i) continue;
            vis[node] = i;
            if (curd == 1e18) continue;

            if ((node / 2 > i and vis[node / 2] < i) and distd[i][node / 2] > distd[i][node] + distu[node]) {
                distd[i][node / 2] = distd[i][node] + distu[node];
                pq.push({distd[i][node / 2], node / 2});
            }

            for (auto& u : edge[node]) {
                if (vis[u.first] < i and distd[i][u.first] > distd[i][node] + u.second) {
                    distd[i][u.first] = distd[i][node] + u.second;
                    pq.push({distd[i][u.first], u.first});
                }
            }
        }
    }

    for (int i = 1 << (n - 1); i < (1 << n); i++) {
        subsz[i] = 1;
        subsm[i] = 0;
    }

    for (int i = (1 << (n - 1)) - 1; i > 0; i--) {
        subsz[i] = subsz[2 * i] + subsz[2 * i + 1] + 1;
        subsm[i] = (subsm[2 * i] + distu[2 * i] * subsz[2 * i] % modval + subsm[2 * i + 1] + distu[2 * i + 1] * subsz[2 * i + 1] % modval) % modval;
    }

    for (int i = 1; i < (1 << n); i++) {
        ans = (ans + subsm[i]) % modval;
        for (int j = i / 2, prv = i; j > 0; j /= 2, prv /= 2) {
            if (distd[j][i] == 1e18) continue;
            ans = (ans + (subsm[j] + modval - (subsm[prv] + distu[prv] * subsz[prv] % modval) % modval) % modval) % modval;
            ans = (ans + (subsz[j] - subsz[prv]) * distd[j][i] % modval) % modval;
        }
    }

    cout << ans << "\n";

	return 0;
}
