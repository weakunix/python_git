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

const int N = 1e4;

int n, ans[2 * N];
set<int> adj[2 * N];

int main() {
    clr(ans, -1);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        
        if (2 * cur > n) {
            cout << "No Answer\n";
            return 0;
        }
        
        int a = (i + cur) % n + n, b = (i + n - cur) % n + n;

        adj[i].insert(a);
        adj[i].insert(b);
        adj[a].insert(i);
        adj[b].insert(i);
    }

    queue<int> q;
    for (int i = 0; i < 2 * n; i++) {
        if (adj[i].empty()) {
            cout << "No Answer\n";
            return 0;
        }
        if (adj[i].size() == 1) q.push(i);
    }

    while (q.size()) {
        int node = q.front();
        q.pop();
        if (ans[node] != -1) continue;

        if (adj[node].empty()) {
            cout << "No Answer\n";
            return 0;
        }

        int nxt = *adj[node].begin();
        ans[nxt] = node;
        ans[node] = nxt;

        for (int i : adj[nxt]) {
            adj[i].erase(nxt);
            if (adj[i].size() == 1) q.push(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] != -1) continue;
        int a = i, b = *adj[i].begin();
        ans[a] = b;
        ans[b] = a;
        while (true) {
            a = -1;
            for (int j : adj[b]) if (ans[j] == -1) a = j;

            if (a == -1) break;

            b = -1;
            for (int j : adj[a]) if (ans[j] == -1) b = j;
            assert(b != -1);

            ans[a] = b;
            ans[b] = a;
        }
    }

    for (int i = 0; i < n; i++) cout << ans[i] - n << (i == n - 1 ? "\n" : " ");

	return 0;
}
