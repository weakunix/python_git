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

int n, m, subsz[S];
ll distu[S], subsm[S], ans = 0;
map<int, ll> edge[S], distd[S];

int main() {
    cin >> n >> m;
    for (int i = 2; i < (1 << n); i++) cin >> distu[i];
    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        if (edge[a][b]) setmn(edge[a][b], c);
        else edge[a][b] = c;
    }

    for (int i = (1 << n) - 1; i > 0; i--) {
        vector<int> pars;
        vector<bool> done;
        priority_queue<simps, vector<simps>, greater<simps>> pq;
        for (int j = i / 2; j > 0; j /= 2) {
            pars.pb(j);
            done.pb(false);

            if (2 * i < (1 << n)) distd[j][i] = min({distd[j][2 * i] + distu[2 * i], distd[j][2 * i + 1] + distu[2 * i + 1], (ll) 1e18});
            else distd[j][i] = 1e18;

            if (edge[j][i]) setmn(distd[j][i], edge[j][i]);

            pq.push({distd[j][i], pars.size() - 1});
        }

        while (pq.size()) {
            int idx = pq.top().second;
            ll curd = pq.top().first;
            pq.pop();
            
            if (done[idx]) continue;
            done[idx] = true;
            if (curd == 1e18) continue;

            if (idx and not done[idx - 1]) {
                if (distd[pars[idx - 1]][i] > curd + distu[pars[idx - 1]]) {
                    distd[pars[idx - 1]][i] = curd + distu[pars[idx - 1]];
                    pq.push({distd[pars[idx - 1]][i], idx - 1});
                }
            }

            for (int j = idx + 1; j < pars.size(); j++) {
                if (done[j]) continue;
                if (edge[pars[j]][pars[idx]] and distd[pars[j]][i] > curd + edge[pars[j]][pars[idx]]) {
                    distd[pars[j]][i] = curd + edge[pars[j]][pars[idx]];
                    pq.push({distd[pars[j]][i], j});
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
        cout << i << " " << ans << "\n";
    }

    cout << ans << "\n";

	return 0;
}
