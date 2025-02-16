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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

int n, q;
vector<int> stck;

int getl(int node) {
    int res = 2 * node % n;
    return (res == 0 ? n : res);
}

int getr(int node) {
    int res = (2 * node + 1) % n;
    return (res == 0 ? n : res);
}

bool dfs(int node, int tar, int dep) {
    stck.pb(node);
    if (node == tar) return true;
    if (dep == 10) {
        stck.bp();
        return false;
    }
    if (dfs(getl(node), tar, dep + 1)) return true;
    if (dfs(getr(node), tar, dep + 1)) return true;
    stck.bp();
    return false;
}

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cout << getl(i) << " " << getr(i) << "\n";
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        assert(dfs(u, v, 0));
        cout << stck.size() - 1 << " ";
        for (int j = 1; j < stck.size(); j++) cout << stck[j] << " ";
        cout << "\n";
        stck.clear();
    }
	return 0;
}
