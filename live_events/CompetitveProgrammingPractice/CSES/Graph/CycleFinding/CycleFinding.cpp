#include <iostream>
#include <cstring>
#include <vector>
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

int n, m;
vector<int> prv;
vector<ll> dist;
vector<threesome> edges;

int main() {
    cin >> n >> m;
    prv.resize(n, -1);
    dist.resize(n, 1e18); dist[0] = 0;
    edges.resize(m);
    for (threesome& t : edges) {
        cin >> t.first >> t.sec >> t.third;
        t.first--; t.sec--;
    }
    for (int i = 0; i < n - 1; i++) {
        for (threesome t : edges) {
            if (dist[t.sec] <= dist[t.first] + t.third) continue;
            dist[t.sec] = dist[t.first] + t.third;
            prv[t.sec] = t.first;
        }
    }
    for (threesome t : edges) {
        if (dist[t.sec] <= dist[t.first] + t.third) continue;
        prv[t.sec] = t.first;
        int cur = t.sec;
        for (int i = 0; i < n; i++) cur = prv[cur];
        vector<ll> ans = {cur};
        cur = prv[cur];
        while (cur != ans[0]) {
            ans.push_back(cur);
            cur = prv[cur];
        }
        ans.push_back(ans[0]);
        cout << "YES\n";
        for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i] + 1 << " ";
        cout << "\n";
        return 0;
    }
    cout << "NO\n";
	return 0;
}
