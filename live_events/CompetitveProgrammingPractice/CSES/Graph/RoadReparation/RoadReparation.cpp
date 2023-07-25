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

int n, m, cnt = 0;
ll ans = 0;
vector<int> par;
vector<threesome> edges;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

bool merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return false;
    if (a < b) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return true;
}

int main() {
    cin >> n >> m;
    par.resize(n, -1);
    edges.resize(m);
    for (threesome& t : edges) {
        cin >> t.sec >> t.third >> t.first;
        t.sec--; t.third--;
    }
    sort(all(edges));
    for (threesome t : edges) {
        if (not merge(t.sec, t.third)) continue;
        cnt++;
        ans += t.first;
        if (cnt == n - 1) {
            cout << ans << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
