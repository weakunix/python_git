#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <map>
#include <unordered_map>
#include <complex>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef complex<ll> pt;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define x real()
#define y imag()

const int N = 1e5 + 2, dir[2][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}};

int n, xcnt = 1, ycnt = 1, ori[N], adj[N][4];
pt cows[N];
priority_queue<threesome> sthor, stver, enhor, enver;

bool cmprow(int a, int b) {
    return cows[a].x < cows[b].x;
}


bool cmpcol(int a, int b) {
    return cows[a].y < cows[b].y;
}

void inpt() {
    int bx, by;
    set<int> sx, sy;
    unordered_map<int, int> compx, compy;

    cin >> n >> bx >> by;
    n += 2;
    cows[1] = {bx, by};

    sx.insert(0);
    sy.insert(0);
    sx.insert(bx);
    sy.insert(by);
    
    for (int i = 2; i < n; i++) {
        int curx, cury;
        char t;

        cin >> curx >> cury >> t;

        cows[i] = {curx, cury};
        sx.insert(curx);
        sy.insert(cury);
        ori[i] = (t != '/');
    }

    for (int i : sx) {
        compx[i] = xcnt;
        xcnt++;
    }
    xcnt++;

    for (int i : sy) {
        compy[i] = ycnt;
        ycnt++;
    }
    ycnt++;

    for (int i = 0; i < n; i++) cows[i] = {compx[cows[i].x], compy[cows[i].y]};

    /*
    //DEBUG
    for (int i = 0; i < n; i++) cout << ori[i] << " ";
    cout << "\n" << xcnt << " " << ycnt << "\n";
    for (int i = 0; i < n; i++) cout << cows[i] << "\n";
    *///

    return;
}

void genadj() {
    vector<vector<int>> rows(ycnt), cols(xcnt);

    for (int i = 0; i < n; i++) {
        rows[cows[i].y].push_back(i);
        cols[cows[i].x].push_back(i);
    }

    for (vector<int>& v : rows) {
        if (v.empty()) continue;

        sort(all(v), cmprow);

        for (int i = 0; i < v.size() - 1; i++) {
            adj[v[i]][1] = v[i + 1];
            adj[v[i + 1]][3] = v[i];
        }

        adj[v[0]][3] = -1;
        adj[v.back()][1] = -1;
    }

    for (vector<int>& v : cols) {
        if (v.empty()) continue;

        sort(all(v), cmpcol);

        for (int i = 0; i < v.size() - 1; i++) {
            adj[v[i]][0] = v[i + 1];
            adj[v[i + 1]][2] = v[i];
        }

        adj[v[0]][2] = -1;
        adj[v.back()][0] = -1;
    }

    /*
    //DEBUG
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) cout << adj[i][j] << " ";
        cout << "\n";
    }
    *///

    return;
}

void genst() {
    int curdir = 0, node = 0;
    while (adj[node][curdir] != -1) {
        int nw = adj[node][curdir];
        if (curdir % 2) sthor.push({-min(cows[node].x, cows[nw].x), {-max(cows[node].x, cows[nw].x), cows[node].y}});
        else stver.push({-cows[node].x, {min(cows[node].y, cows[nw].y), max(cows[node].y, cows[nw].y)}});

        node = nw;
        curdir = dir[ori[node]][curdir];
    }

    if (curdir == 0) stver.push({-cows[node].x, {cows[node].y, ycnt - 1}});
    else if (curdir == 1) sthor.push({-cows[node].x, {-(xcnt - 1), cows[node].y}});
    else if (curdir == 2) stver.push({-cows[node].x, {0, cows[node].y}});
    else sthor.push({0, {-cows[node].x, cows[node].y}});

    return; //DEBUG HERE
}

void genen() {
    bool vis[4];
    memset(vis, false, sizeof(vis));

    for (int i = 0; i < 4; i++) {
        if (vis[i]) continue;

        int curdir = i, node = 1;
        bool works = true;
        while (adj[node][curdir] != -1) {
            int nw = adj[node][curdir];
            if (curdir % 2) enhor.push({-min(cows[node].x, cows[nw].x), {-max(cows[node].x, cows[nw].x), cows[node].y}});
            else enver.push({-cows[node].x, {min(cows[node].y, cows[nw].y), max(cows[node].y, cows[nw].y)}});

            if (nw == 0) {
                works = false;
                break;
            }

            if (nw == 1) {
                vis[(curdir + 2) % 4] = true;
                works = false;
                break;
            }

            node = nw;
            curdir = dir[ori[node]][curdir];
        }

        if (not works) continue;

        if (curdir == 0) enver.push({-cows[node].x, {cows[node].y, ycnt - 1}});
        else if (curdir == 1) enhor.push({-cows[node].x, {-(xcnt - 1), cows[node].y}});
        else if (curdir == 2) enver.push({-cows[node].x, {0, cows[node].y}});
        else enhor.push({0, {-cows[node].x, cows[node].y}});
    }

    return; //DEBUG HERE
}

void setbit(vector<int>& bit, int idx, int change) {
    for (idx++; idx <= ycnt; idx += idx & (-idx)) bit[idx] += change;
    return;
}

ll getbit(vector<int>& bit, int idx) {
    ll res = 0;
    for (idx++; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

ll getans(priority_queue<threesome>& hor, priority_queue<threesome>& ver) {
    ll res = 0;
    vector<int> bit(ycnt + 1);
    priority_queue<simps> rem;

    while (hor.size() or ver.size()) {
        int cur = max({hor.size() ? hor.top().first : -1e9, ver.size() ? ver.top().first : -1e9, rem.size() ? rem.top().first : -1e9});
        
        while (rem.size() and rem.top().first == cur) {
            setbit(bit, rem.top().second, -1);
            rem.pop();
        }

        while (ver.size() and ver.top().first == cur) {
            res += getbit(bit, ver.top().third) - getbit(bit, ver.top().sec - 1);
            ver.pop();
        }
        
        while (hor.size() and hor.top().first == cur) {
            setbit(bit, hor.top().third, 1);
            rem.push(hor.top().second);
            hor.pop();
        }
    }

    return res;
}

int main() {
    freopen("optics.in", "r", stdin);
    freopen("optics.out", "w", stdout);

    cows[0] = {0, 0};
    ori[0] = -1;
    ori[1] = -1;

    inpt();
    genadj();
    genst();
    genen();

    cout << getans(enhor, stver) + getans(sthor, enver) << "\n";
	return 0;
}
