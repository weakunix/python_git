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

int n, m, cnt, mx = 1;
vector<int> par;

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
    mx = max(-par[b], mx);
    par[a] = b;
    return true;
}

int main() {
    cin >> n >> m;
    cnt = n;
    par.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (merge(a, b)) cnt--;
        cout << cnt << " " << mx << "\n";
    }
	return 0;
}
