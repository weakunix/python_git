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

const int N = 2e5;

int n, q, cnt = 0, to[30][N], group[N], dep[N], idx[N];
bool visited[N];
vector<int> groupsz;

int findnext(int node, int k) {
    for (int i = 0; i < 30; i++) {
        if (k & (1 << i)) node = to[i][node];
    }
    return node;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    memset(group, -1, sizeof(group));
    memset(visited, false, sizeof(visited));

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> to[0][i];
        to[0][i]--;
    }
    for (int i = 1; i < 30; i++) {
        for (int j = 0; j < n; j++) to[i][j] = to[i - 1][to[i - 1][j]];
    }
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        int node = i, sz = 0;
        vector<int> stck;
        while (not visited[node]) {
            stck.push_back(node);
            visited[node] = true;
            node = to[0][node];
        }
        if (group[node] == -1) {
            while (stck.back() != node) {
                int cur = stck.back();
                stck.pop_back();
                group[cur] = cnt;
                dep[cur] = 0;
                idx[cur] = sz;
                sz++;
            }
            stck.pop_back();
            group[node] = cnt;
            dep[node] = 0;
            idx[node] = sz;
            groupsz.push_back(sz + 1);
            cnt++;
        }
        sz = dep[node] + 1;
        while (not stck.empty()) {
            int cur = stck.back();
            stck.pop_back();
            group[cur] = group[node];
            dep[cur] = sz;
            sz++;
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (group[a] != group[b] or dep[a] < dep[b]) {
            cout << "-1\n";
            continue;
        }
        if (dep[a] == 0) {
            int ans = idx[a] - idx[b];
            if (ans < 0) ans += groupsz[group[a]];
            cout << ans << "\n";
            continue;
        }
        if (dep[b] == 0) {
            int cur = findnext(a, dep[a]), ans = idx[cur] - idx[b];
            if (ans < 0) ans += groupsz[group[cur]];
            cout << ans + dep[a] << "\n";
            continue;
        }
        cout << (findnext(a, dep[a] - dep[b]) == b ? dep[a] - dep[b] : -1) << "\n";
    }
	return 0;
}
