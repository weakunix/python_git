#include <iostream>
#include <vector>
#include <utility>
#include <map>
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

int n, m, q;
vector<ll> mana;
vector<threesome> edges;

int main() {
    cin >> n >> m;
    mana.resize(n);
    edges.resize(m);
    for (int i = 0; i < n; i++) cin >> mana[i];
    for (int i = 0; i < m; i++) cin >> edges[i].sec >> edges[i].third >> edges[i].first;
    sort(all(edges));
	return 0;
}
