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
typedef pair<int, int> simps;
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

const int N = 3e4;

int q, par[N], idx[N];

int getpar(int node) {
    if (par[node] < 0) return node;
    int nwpar = getpar(par[node]);
    idx[node] += idx[par[node]];
    par[node] = nwpar;
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    idx[a] = -par[b];
    par[b] += par[a];
    par[a] = b;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    clr(par, -1);
    clr(idx, 0);

    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        char t;
        cin >> t >> u >> v;
        u--; v--;
        if (t == 'M') merge(u, v);
        else cout << (getpar(u) != getpar(v) ? -1 : abs(idx[u] - idx[v]) - 1) << "\n";
    }

	return 0;
}
