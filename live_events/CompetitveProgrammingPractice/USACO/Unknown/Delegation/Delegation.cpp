#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 1e5;

int n;
vector<int> adj[N];

int dfs(int node, int parent, int k) {
    int uppath = -1;
    multiset<int> lens;

    for (int i : adj[node]) {
        if (i != parent) {
            int cur = dfs(i, node, k);
            if (cur == -1) return -1;
            lens.insert(cur);
        }
    }

    if (lens.empty()) return 1;
    if (lens.size() == 1) return *lens.begin() + 1;

    while (lens.size() > 2) {
        int cur = *lens.begin();
        lens.erase(lens.begin());
        
        if (cur >= k) continue;
        
        auto it = lens.lower_bound(k - cur);
        if (it == lens.end()) {
            if (uppath == -1 and node != 0) {
                uppath = cur;
                continue;
            }
            return -1;
        }
        lens.erase(it);
    }

    if (lens.size() == 1) {
        if (uppath == -1) return *lens.begin() + 1;
        if (*lens.begin() < k) return -1;
        return uppath + 1;
    }

    int a = *lens.begin(), b;
    lens.erase(lens.begin());
    b = *lens.begin();

    if (uppath != -1) {
        if (a + b >= k) return uppath + 1;
        return -1;
    }

    if (a >= k) return b + 1;
    if (b >= k) return a + 1;
    if (a + b >= k) return 1;
    return -1;
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int l = 1, r = n - 1;
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (dfs(0, -1, mid) != -1) l = mid;
        else r = mid - 1;
    }

    assert(l == r);
    cout << l << "\n";

	return 0;
}
