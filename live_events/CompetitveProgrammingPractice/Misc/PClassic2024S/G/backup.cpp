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

const int K = 1e5 + 4;

struct Rect {
    int id, l, d, r, u;

    Rect() : id(-1), l(-1), d(-1), r(-1), u(-1) {}

    Rect(int ID, int L, int D, int R, int U) : id(ID), l(L), d(D), r(R), u(U) {}

    ~Rect() {}
};

int n, m, k, vis[K], ans = 1e9;
vector<int> adj[K];
map<int, vector<int>> onleft, ondown, onright, onup;
Rect arr[K];

void addedge(int a, int b) {
    adj[a].pb(b);
    adj[b].pb(a);
    return;
}

bool cmpx(Rect& a, Rect& b) {
    return a.l < b.l;
}

bool cmpy(Rect& a, Rect& b) {
    return a.d < b.d;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 4; i < k + 4; i++) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;

        arr[i] = Rect(i, l, d, r, u);

        if (l == 0) addedge(0, i);
        if (d == 0) addedge(3, i);
        if (r == n - 1) addedge(1, i);
        if (u == m - 1) addedge(2, i);
    
        onleft[r].pb(i);
        ondown[u].pb(i);
        onright[l].pb(i);
        onup[d].pb(i);
    }

    for (auto& u : onleft) {
        if (not onright.count(u.first)) continue;

        vector<int>& lside = u.second, rside = onright[u.first];
        sort(all(lside), cmpy);
        sort(all(rside), cmpy);

        int a = 0, b = 0;
        while (a < lside.size() and b < rside.size()) {
            Rect curl = lside[arr[a]], curr = rside[arr[b]];
            if (curl.u == curr.u) {
                addedge(curl.id, curr.id);
                if (a < lside.size() - 1 and lside[a + 1].d == curr.u) addedge(lside[a + 1].id, curr.id);
                if (b < rside.size() - 1 and rside[b + 1].d == curl.u) addedge(rside[b + 1].id, curl.id);
                a++;
                b++;
                continue;
            }
            if (curl.u < curr.u) {
                if (curr.d <= curl.u) addedge(curl.id, curr.id);
                a++;
                continue;
            }
            if (curl.u > curr.u) {
                if (curl.d <= curr.u) addedge(curl.id, curr.id);
                b++;
                continue;
            }
        }
    }

    for (auto& u : ondown) {
        if (not onup.count(u.first)) continue;

        vector<int>& dside = u.second, uside = onup[u.first].second;
        sort(all(dside), cmpx);
        sort(all(uside), cmpx);

        int a = 0, b = 0;
        while (a < dside.size() and b < uside.size()) {
            int curd = dside[a], curu = uside[b];
            if (curd.r == curu.r) {
                addedge(curd.id, curu.id);
                if (a < dside.size() - 1 and dside[a + 1].l == curu.r) addedge(dside[a + 1].id, curu.id);
                if (b < uside.size() - 1 and uside[b + 1].l == curd.r) addedge(uside[b + 1].id, curd.id);
                a++;
                b++;
                continue;
            }
            if (curd.r < curu.r) {
                if (curu.l <= curd.u) addedge(curd.id, curu.id);
                a++;
                continue;
            }
            if (curd.u > curu.u) {
                if (curd.l <= curu.u) addedge(curd.id, curu.id);
                b++;
                continue;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        clr(vis, -1);
        queue<int> q;

        vis[i] = 0;
        q.push(i);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            if (cur < 4 and (cur + i) % 2 != 0) {
                setmn(ans, vis[cur] - 1);
                break;
            }

            for (int j : adj[cur]) {
                if (vis[j] != -1) continue;
                vis[j] = vis[cur] + 1;
                q.push(j);
            }
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << "\n";

	return 0;
}
