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
#include <cmath>
#include <numeric>
#include <cassert>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef pair<double, double> simps;
typedef pair<double, simps> threesome;

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

const int N = 10, M = 100100;
const double eps = 1e-7;

struct Line {
    double m, b, l, r;

    Line() : m(0), b(0), l(-1), r(-1) {}

    Line(double _m, double _b, double _l, double _r) : m(_m), b(_b), l(_l), r(_r) {}

    ~Line() {}

    double get(double x) {
        return m * x + b;
    }
};

double intersect(Line a, Line b) {
    return (a.b - b.b) / (b.m - a.m);
}

int n, w, t, v, m = 0;
double len[N], ans = 0;
vector<int> arr[N];
set<double> pts;
Line lines[M];

int cmp(double a, double b) {
    if (fabs(a - b) < eps) return 0;
    return (a - b < 0 ? -1 : 1);
}

void addline(int idx, double k, double a, double b, double l, double r) {
    if (idx != -1) arr[idx].pb(m);
    lines[m] = Line(k, b - k * a, l, r);
    m++;
    return;
}

void process(int idx, double l, double r, double s) {
    if (cmp(s, 0) == 0) {
        addline(idx, 0, 0, l, 0, t);
        addline(-1, 0, 0, r, 0, t);
        return;
    }
    if (cmp(l, 0) == 0 and cmp(s, 0) == -1) s = -s;
    if (cmp(r, w) == 0 and cmp(s, 0) == 1) s = -s;

    double curx = 0;
    while (true) {
        if (cmp(s, 0) == 1) {
            assert(cmp(r, w) == -1);
            double nwx = curx + (w - r) / s;
            bool done = (cmp(nwx, t) != -1);

            if (done) nwx = t;

            addline(idx, s, curx, l, curx, nwx);
            addline(-1, s, curx, r, curx, nwx);

            if (done) break;

            l += w - r;
            r = w;
            curx = nwx;
            s = -s;
        }
        else {
            assert(cmp(l, 0) == 1);
            s = -s;
            double nwx = curx + l / s;
            bool done = (cmp(nwx, t) != -1);
            
            if (done) nwx = t;
            
            addline(idx, -s, curx, l, curx, nwx);
            addline(-1, -s, curx, r, curx, nwx);

            if (done) break;

            r -= l;
            l = 0;
            curx = nwx;
        }
    }

    return;
}

double f(double x) {
    vector<simps> v;
    for (int i = 0; i < n; i++) {
        for (int j : arr[i]) {
            if (cmp(x, lines[j].r) == 1) continue;
            double l = lines[j].get(x);
            v.pb({l, l + len[i]});
            break;
        }
    }

    sort(all(v));

    double res = 0, curx = 0;
    for (simps& s : v) {
        if (cmp(curx, s.first) == -1) res += s.first - curx;
        setmx(curx, s.second);
    }
    if (cmp(curx, w) == -1) res += w - curx;
    return res;
}

int main() {
    cin >> n >> w >> t >> v;
    for (int i = 0; i < n; i++) {
        double x, l, s;
        cin >> x >> l >> s;
        len[i] = l;
        if (cmp(l, w) == 0) {
            cout << "0.00\n";
            return 0;
        }
        process(i, x, x + l, s);
    }

    for (int i = 0; i < m; i++) {
        pts.insert(lines[i].l);
        pts.insert(lines[i].r);
        for (int j = i + 1; j < m; j++) {
            if (cmp(lines[i].m, lines[j].m) == 0) continue;
            double x = intersect(lines[i], lines[j]);
            if (cmp(x, lines[i].l) == -1 or cmp(x, lines[i].r) == 1) continue;
            if (cmp(x, lines[j].l) == -1 or cmp(x, lines[j].r) == 1) continue;
            pts.insert(x);
        }
    }

    double curx = 0;
    for (double i : pts) {
        if (cmp(i, curx) == 0) continue;
        ans += (f(curx) + f(i)) * (i - curx) / 2;
        curx = i;
    }

    cout << fixed << setprecision(2) << v * ans << "\n";

	return 0;
}
