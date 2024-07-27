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

int n, m, subsz[S], vis[S], dep[S];
ll edge[S][N], distu[S], distd[S][N], subsm[S], ans = 0;
vector<int> downedge[S];

int main() {
    clr(vis, 0);
    clr(edge, 0);

    dep[1] = 1;
    for (int i = 2; i < S; i++) dep[i] = dep[i / 2] + 1;

    cin >> n >> m;
    for (int i = 2; i < (1 << n); i++) cin >> distu[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        if (edge[b][dep[b] - dep[a]]) setmn(edge[b][dep[b] - dep[a]], c);
        else edge[b][dep[b] - dep[a]] = c;
        downedge[a].pb(b);
    }

    for (int i = 1; i < (1 << n); i++) {
        queue<int> q;
        priority_queue<simps, vector<simps>, greater<simps>> pq;

        q.push(2 * i);
        q.push(2 * i + 1);
        while (q.front() < (1 << n)) {
            int node = q.front();
            q.pop();

            distd[node][dep[node] - dep[i]] = (edge[node][dep[node] - dep[i]] ? edge[node][dep[node] - dep[i]] : 1e18);
            if (i > 1) setmn(distd[node][dep[node] - dep[i]], distd[node][dep[node] - dep[i / 2]] + distu[i]);
            pq.push({distd[node][dep[node] - dep[i]], node});

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

            if ((node / 2 > i and vis[node / 2] < i) and distd[node / 2][dep[node / 2] - dep[i]] > curd + distu[node]) {
                distd[node / 2][dep[node / 2] - dep[i]] = curd + distu[node];
                pq.push({distd[node / 2][dep[node / 2] - dep[i]], node / 2});
            }

            for (int j : downedge[node]) {
                if (vis[j] < i and distd[j][dep[j] - dep[i]] > curd + edge[j][dep[j] - dep[node]]) {
                    distd[j][dep[j] - dep[i]] = curd + edge[j][dep[j] - dep[node]];
                    pq.push({distd[j][dep[j] - dep[i]], j});
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
            if (distd[i][dep[i] - dep[j]] == 1e18) continue;
            ans = (ans + (subsm[j] + modval - (subsm[prv] + distu[prv] * subsz[prv] % modval) % modval) % modval) % modval;
            ans = (ans + (subsz[j] - subsz[prv]) * distd[i][dep[i] - dep[j]] % modval) % modval;
        }
    }

    cout << ans << "\n";

	return 0;
}
