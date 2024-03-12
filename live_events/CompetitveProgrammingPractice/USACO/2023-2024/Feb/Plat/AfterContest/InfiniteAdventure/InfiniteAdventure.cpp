#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, ll> simps;
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

const int N = 1e5, L = 62;
ll MX = 1e18;

int n, q, t[N];
vector<simps> dp1[N], dp2[N]; //dp1: next in same layer, dp2: next in higher layer
vector<bool> vis[N];
vector<int> adj[N];
vector<vector<simps>> nxt[N];

struct GenDP {
    GenDP() {}

    ~GenDP() {}

    void getdp(int node, ll tm) {
        tm %= t[node];

        if (vis[node][tm]) return;
        vis[node][tm] = true;

        int cur = adj[node][tm];
        if (t[cur] == t[node]) { //same layer
            dp1[node][tm] = {cur, 1};
            dp2[node][tm] = getdp2(cur, tm + 1);
            if (dp2[node][tm].first != -1) dp2[node][tm].second++;
        }
        else if (t[cur] > t[node]) dp2[node][tm] = {cur, 1}; //higher layer
        else { //lower layer
            ll timespent = 1;
            while (true) {
                simps nxthi = getdp2(cur, tm + timespent);
                cur = nxthi.first;
                if (cur == -1) break;
                timespent += nxthi.second;
                if (timespent > MX) break;
                if (t[cur] == t[node]) dp1[node][tm] = {cur, timespent}; //reach same layer
                if (t[cur] > t[node]) {
                    dp2[node][tm] = {cur, timespent}; //reach higher layer
                    break;
                }
            }
        }

        return;
    }

    simps getdp1(int node, ll tm) {
        tm %= t[node];
        getdp(node, tm);
        return dp1[node][tm];
    }

    simps getdp2(int node, ll tm) {
        tm %= t[node];
        getdp(node, tm);
        return dp2[node][tm];
    }
} gen;

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        dp1[i].resize(t[i], {-1, -1});
        dp2[i].resize(t[i], {-1, -1});
        vis[i].resize(t[i]);
        nxt[i].resize(t[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t[i]; j++) {
            int cur;
            cin >> cur;
            cur--;
            adj[i].pb(cur);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t[i]; j++) {
            simps cur = gen.getdp1(i, j);
            if (cur.first != -1) nxt[i][j].pb(cur);
        }
    }

    for (int k = 1; k < L; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < t[i]; j++) {
                if (nxt[i][j].size() < k) continue;
                simps cur = nxt[i][j][k - 1];
               
                if (nxt[cur.first][(j + cur.second) % t[cur.first]].size() < k) continue;
                simps cur2 = nxt[cur.first][(j + cur.second) % t[cur.first]][k - 1];

                if (cur.second + cur2.second <= MX) nxt[i][j].pb({cur2.first, cur.second + cur2.second});
            }
        }
    }

    for (int k = 0; k < q; k++) {
        int node;
        ll tm, remt;
        cin >> node >> tm >> remt;
        node--;

        simps cur = gen.getdp2(node, tm);
        while (cur.first != -1 and cur.second <= remt) {
            node = cur.first;
            tm += cur.second;
            remt -= cur.second;
            cur = gen.getdp2(node, tm);
        }

        while (remt) {
            for (int i = L - 1; i >= 0; i--) {
                if (nxt[node][tm % t[node]].size() <= i) continue;

                cur = nxt[node][tm % t[node]][i];
                if (cur.second > remt) continue;
                node = cur.first;
                tm += cur.second;
                remt -= cur.second;
            }

            if (not remt) break;

            node = adj[node][tm % t[node]];
            tm++;
            remt--;
        }

        cout << node + 1 << "\n";
    }

	return 0;
}
