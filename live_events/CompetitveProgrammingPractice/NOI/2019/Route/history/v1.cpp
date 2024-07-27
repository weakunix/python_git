#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <complex>
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

const int N = 1e5, M = 2e5;

struct Line {
    ll m, b, t;

    Line() : m(0), b(0), t(0) {}

    Line(ll _m, ll _b, ll _t) : m(_m), b(_b), t(_t) {}

    ~Line() {}

    ll get(ll x) {
        return m * x + b;
    }
};

bool operator<(Line a, Line b) {
    return a.t > b.t;
}

struct CHT {
    deque<Line> dq;
    priority_queue<Line> toadd;
    
    CHT() {}

    ~CHT() {}

    bool replace(Line& r) {
        if (dq.size() <= 1) return false;
        Line& l = dq[dq.size() - 2];
        Line& m = dq.back();
        return (r.b - m.b) * (l.m - r.m) <= (r.b - l.b) * (m.m - r.m);
    }

    void add(Line l) {
        if (dq.size() and dq.back().m == l.m) {
            if (dq.back().b >= l.b) return;
            dq.bp();
        }
        while (replace(l)) dq.bp();
        dq.pb(l);
        return;
    }

    int get(int x) {
        while (toadd.size() and toadd.top().t <= x) {
            add(toadd.top());
            toadd.pop();
        }
        if (dq.empty()) return -1;
        while (dq.size() > 1 and dq[0].get(x) <= dq[1].get(x)) dq.pop_front();
        return dq[0].get(x);
    }
};

int n, m, a, b, c;
ll ans = 1e18;
vector<int> edges[M];
CHT cht[N];

int main() {
    cin >> n >> m >> a >> b >> c;
    b++;
    for (int i = 0; i < m; i++) {
        int u, v, p, q;
        cin >> u >> v >> p >> q;
        edges[i] = {p, q, u - 1, v - 1};
    }
    sort(edges, edges + m);

    cht[0].add(Line(0, 0, 0));

    for (int i = 0; i < m; i++) {
        int u = edges[i][2], v = edges[i][3], p = edges[i][0], q = edges[i][1];
        ll cost = a * p * p + b * p + c - cht[u].get(p) + q - p;
        cht[v].toadd.push(Line(2 * a * q, -(a * q * q - b * q + cost), q));
        if (v == n - 1) setmn(ans, cost);
    }

    cout << ans << "\n";

	return 0;
}
