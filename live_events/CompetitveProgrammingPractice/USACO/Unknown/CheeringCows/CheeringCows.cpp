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

const int N = 1e4, P = 1e5;

int n, p, ans = 1e9, arr[N], par[N];
threesome edges[P];

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

bool merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return false;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return true;
}

int main() {
    memset(par, -1, sizeof(par));

    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ans = min(arr[i], ans);
    }
    for (int i = 0; i < p; i++) {
        cin >> edges[i].sec >> edges[i].third >> edges[i].first;
        edges[i].sec--;
        edges[i].third--;
        edges[i].first = 2 * edges[i].first + arr[edges[i].sec] + arr[edges[i].third];
    }
    sort(edges, edges + p);
    
    for (int i = 0; i < p; i++) if (merge(edges[i].sec, edges[i].third)) ans += edges[i].first;

    cout << ans << "\n";

	return 0;
}
