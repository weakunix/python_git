#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 1e5;

int n, k, curcnt = 0;
vector<int> adj[N];

int dfs(int node, int parent, int tar) {
    priority_queue<int> pq;

    for (int i : adj[node]) if (i != parent) pq.push(dfs(i, node, tar) + 1);

    while (pq.size() and pq.top() > tar) {
        assert(pq.top() == tar + 1);
        pq.pop();
        curcnt++;
    }

    if (pq.empty()) return 0;

    int prv = pq.top();
    pq.pop();

    while (pq.size() and prv + pq.top() > tar) {
        prv = pq.top();
        pq.pop();
        curcnt++;
    }

    return prv;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int l = 0, r = n - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        curcnt = 0;
        dfs(0, -1, mid);
        if (curcnt <= k) r = mid;
        else l = mid + 1;
    }

    assert(l == r);
    cout << l << "\n";

	return 0;
}
