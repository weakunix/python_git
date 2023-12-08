#include <iostream>
#include <string>
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

const int N = 101;

int n, p[N], ht[N];
vector<int> adj[N];

bool dep2() {
    for (int i = 2; i <= n; i++) {
        if (p[i] != 1) return false;
    }

    cout << 1 << "\n";
    for (int i = 0; i < n - 1; i++) cout << 1 << " ";
    cout << endl;

    int inpt;
    cin >> inpt;
    if (inpt == 1 or inpt == -1) return true;

    cin >> inpt;
    cout << inpt << endl;

    cin >> inpt;
    assert(inpt == 1);

    return true;
}

void dfs(int node, int height) {
    ht[node] = height;
    for (int i : adj[node]) dfs(i, height + 1);
    return;
}

bool nodeg1() {
    for (int i = 2; i <= n; i++) {
        if (adj[i].size() == 1) return false;
    }

    cout << 2 << "\n";
    for (int i = 2; i <= n; i++) cout << (ht[i] % 2 ? 2 : 1) << " ";
    cout << endl;

    while (true) {
        int inpt;
        cin >> inpt;
        if (inpt == 1 or inpt == -1) return true;

        int cnt1, cnt2;
        cin >> cnt1 >> cnt2;
        assert(cnt1 == 1 xor cnt2 == 1);

        if (cnt1 == 1) cout << 1 << endl;
        else cout << 2 << endl;
    }

    return true;
}

bool try2() {
    int ans[N];
    queue<int> qup, qdown;
    memset(ans, 0, sizeof(ans));

    for (int i = 2; i <= n; i++) {
        if (adj[i].size() == 1) {
            if (ans[i] and ans[i] != 1) return false;
            ans[i] = 1;
            if (ans[adj[i][0]] and ans[adj[i][0]] != 2) return false;
            ans[adj[i][0]] = 2;
            qup.push(i);
            qdown.push(adj[i][0]);
        }
    }

    while (qup.size()) {
        int cur = qup.front(), newans = (ans[cur] == 1 ? 2 : 1);
        qup.pop();
        if (p[cur] == 1) continue;
        if (ans[p[cur]] and ans[p[cur]] != newans) return false;
        if (ans[p[cur]] == newans) continue;
        ans[p[cur]] = newans;
        qup.push(p[cur]);
    }

    while (qdown.size()) {
        int cur = qdown.front(), newans = (ans[cur] == 1 ? 2 : 1);
        qdown.pop();
        for (int i : adj[cur]) {
            if (ans[i] and ans[i] != newans) return false;
            if (ans[i] == newans) continue;
            ans[i] = newans;
            qdown.push(i);
        }
    }

    cout << 2 << "\n";
    for (int i = 2; i <= n; i++) cout << ans[i] << " ";
    cout << endl;

    while (true) {
        int inpt;
        cin >> inpt;
        if (inpt == 1 or inpt == -1) return true;

        int cnt1, cnt2;
        cin >> cnt1 >> cnt2;
        assert(cnt1 == 1 or cnt2 == 1);

        if (cnt1 == 1 and cnt2 == 1) {
            cout << 1 << endl;
            continue;
        }

        if (cnt1 == 1) cout << 1 << endl;
        else cout << 2 << endl;
    }

    return true;
}

int main() {
	cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        adj[p[i]].push_back(i);
    }

    dfs(1, 0);

    if (dep2()) return 0;

    if (nodeg1()) return 0;

    if (try2()) return 0;

    cout << 3 << "\n";
    for (int i = 2; i <= n; i++) cout << (ht[i] % 3 == 0 ? 3 : ht[i] % 3) << " ";
    cout << endl;

    while (true) {
        int inpt;
        cin >> inpt;
        if (inpt == 1 or inpt == -1) return 0;

        int cnt1, cnt2, cnt3;
        cin >> cnt1 >> cnt2 >> cnt3;

        if (cnt1 and (not cnt2 and not cnt3)) cout << 1 << endl;
        else if (cnt2 and (not cnt3 and not cnt1)) cout << 2 << endl;
        else if (cnt3 and (not cnt1 and not cnt2)) cout << 3 << endl;
        else if (cnt1 and cnt2) cout << 1 << endl;
        else if (cnt2 and cnt3) cout << 2 << endl;
        else if (cnt3 and cnt1) cout << 3 << endl;
        else assert(false);

    }

	return 0;
}
