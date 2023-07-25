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

int n, m;
vector<int> par, ans;

int getpar(int node) {
    if (par[node] < 0) return node;
    par[node] = getpar(par[node]);
    return par[node];
}

void merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return;
    if (par[a] < par[b]) swap(a, b);
    par[b] += par[a];
    par[a] = b;
    return;
}

int main() {
    cin >> n >> m;
    par.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        merge(a, b);
    }
    for (int i = 0; i < n; i++) {
        if (par[i] < 0) ans.push_back(i + 1);
    }
    cout << ans.size() - 1 << "\n";
    for (int i = 0; i < ans.size() - 1; i++) cout << ans[i] << " " << ans[i + 1] << "\n";
	return 0;
}
