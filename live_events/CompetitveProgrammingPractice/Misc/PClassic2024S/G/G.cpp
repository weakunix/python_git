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

int n, m, k, vis[K], ans = 1e9, prv[K];
vector<int> adj[K], ansv;
map<int, vector<int>> onleft, ondown, onright, onup;
Rect arr[K];

void addedge(int a, int b) {
    adj[a].pb(b);
    adj[b].pb(a);
    return;
}

bool cmpx(int a, int b) {
    return arr[a].l < arr[b].l;
}

bool cmpy(int a, int b) {
    return arr[a].d < arr[b].d;
}

int main() {
    cin >> n >> m >> k;
    for (int i = 4; i < k + 4; i++) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        r++;
        u++;

        arr[i] = Rect(i, l, d, r, u);

        if (l == 0) addedge(0, i);
        if (d == 0) addedge(3, i);
        if (r == n) addedge(1, i);
        if (u == m) addedge(2, i);
    
        onleft[r].pb(i);
        ondown[u].pb(i);
        onright[l].pb(i);
        onup[d].pb(i);
    }

    for (auto& i : onleft) {
        if (not onright.count(i.first)) continue;

        vector<int>& lside = i.second, rside = onright[i.first];
        sort(all(lside), cmpy);
        sort(all(rside), cmpy);

        int a = 0, b = 0;
        while (a < lside.size() and b < rside.size()) {
            Rect curl = arr[lside[a]], curr = arr[rside[b]];
            if (curl.u == curr.u) {
                addedge(curl.id, curr.id);
                if (a < lside.size() - 1 and arr[lside[a + 1]].d == curr.u) addedge(lside[a + 1], curr.id);
                if (b < rside.size() - 1 and arr[rside[b + 1]].d == curl.u) addedge(rside[b + 1], curl.id);
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

    for (auto& i : ondown) {
        if (not onup.count(i.first)) continue;

        vector<int>& dside = i.second, uside = onup[i.first];
        sort(all(dside), cmpx);
        sort(all(uside), cmpx);

        int a = 0, b = 0;
        while (a < dside.size() and b < uside.size()) {
            Rect curd = arr[dside[a]], curu = arr[uside[b]];
            if (curd.r == curu.r) {
                addedge(curd.id, curu.id);
                if (a < dside.size() - 1 and arr[dside[a + 1]].l == curd.r) addedge(dside[a + 1], curd.id);
                if (b < uside.size() - 1 and arr[uside[b + 1]].l == curu.r) addedge(uside[b + 1], curu.id);
                a++;
                b++;
                continue;
            }
            if (curd.r < curu.r) {
                if (curu.l <= curd.r) addedge(curd.id, curu.id);
                a++;
                continue;
            }
            if (curd.r > curu.r) {
                if (curd.l <= curu.r) addedge(curd.id, curu.id);
                b++;
                continue;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        clr(vis, -1);
        clr(prv, -1);
        queue<int> q;

        vis[i] = 0;
        q.push(i);

        while (not q.empty()) {
            int cur = q.front();
            q.pop();

            if (cur < 4 and (cur + i) % 2 != 0) {
                setmn(ans, vis[cur] - 1);
                if (ans == vis[cur] - 1) {
                    ansv.clear();
                    while (cur != -1) {
                        if (cur >= 4) ansv.pb(cur - 3);
                        cur = prv[cur];
                    }
                }
                break;
            }

            for (int j : adj[cur]) {
                if (vis[j] != -1) continue;
                vis[j] = vis[cur] + 1;
                prv[j] = cur;
                q.push(j);
            }
        }
    }

    cout << (ans == 1e9 ? -1 : ans) << " ";

    if (ans != 1e9) {
        for (int i = ans - 1; i >= 0; i--) cout << ansv[i] << " ";
    }

    cout << "\n";

	return 0;
}
