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

const int N = 2e6;

int t, m, cnt, l[N], r[N], rt, path[N][4], works[N];

bool isleaf(int node) {
    return (l[node] == -1 and r[node] == -1);
}

bool isvalid(int node) {
    if (isleaf(node)) return true;
    if (l[node] == -1) return isvalid(r[node]);
    if (r[node] == -1) return isvalid(l[node]);
    if (isleaf(l[node])) return isvalid(r[node]);
    if (isleaf(r[node])) return isvalid(l[node]);
    return false;
}

void dfs(int& cur, int node) {
    if (cur == -1) {
        cur = cnt;
        cnt++;
    }

    if (isleaf(node)) {
        works[cur] = true;
        return;
    }

    if (l[node] == -1) dfs(path[cur][1], r[node]);
    else if (isleaf(l[node]) and r[node] != -1) dfs(path[cur][3], r[node]);

    if (r[node] == -1) dfs(path[cur][0], l[node]);
    else if (isleaf(r[node]) and l[node] != -1) dfs(path[cur][2], l[node]);

    return;
}

bool ans(int cur) {
    if (cur == -1) return false;
    if (works[cur]) return true;
    for (int i = 0; i < 4; i++) if (not ans(path[cur][i])) return false;
    return true;
}

void subcase() {
    cnt = 0;
    rt = -1;
    clr(path, -1);
    clr(works, false);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> l[j] >> r[j];
            l[j]--; r[j]--;
        }
        if (not isvalid(0)) continue;
        dfs(rt, 0);
    }

    cout << (ans(0) ? "Almost Complete\n" : "No\n");

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
