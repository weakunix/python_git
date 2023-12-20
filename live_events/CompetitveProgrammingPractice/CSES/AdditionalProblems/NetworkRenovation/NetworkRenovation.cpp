#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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
vector<int> adj[N], leaf;

void dfs(int node, int parent) {
    if (adj[node].size() == 1) leaf.push_back(node);
    for (int i : adj[node]) if (i != parent) dfs(i, node);
    return;
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

    dfs(0, -1);

    cout << (leaf.size() + 1) / 2 << "\n";
    for (int i = 0; i < (leaf.size() + 1) / 2; i++) cout << leaf[i] + 1 << " " << leaf[i + leaf.size() / 2] + 1 << "\n";

	return 0;
}
