#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
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

struct Line {
    ll m, y;

    Line(ll mm, ll yy) {
        m = mm;
        y = yy;
        return;
    }

    ll eval(ll x) {
        return m * x + y;
    }
};

double getintersect(Line a, Line b) {
    return (double) (b.y - a.y) / (a.m - b.m);
}

int n;
ll initf, lasts, f[N], s[N], ans;
deque<Line> dq;

int main() {
    cin >> n >> initf;
    n--;
    dq.push_back(Line(initf, 0));
    for (int i = 0; i < n; i++) cin >> s[i];
    cin >> lasts;
    ans = lasts * initf;
    for (int i = 0; i < n; i++) cin >> f[i];

    for (int i = 0; i < n; i++) {
        if (f[i] == initf or (i > 0 and f[i] == f[i - 1])) continue;

        while (dq.size() >= 2 and dq[0].eval(s[i]) >= dq[1].eval(s[i])) dq.pop_front();
        ll cur = dq[0].eval(s[i]);
        ans = min(cur + lasts * f[i], ans);

        Line curline = Line(f[i], cur);
        while (dq.size() and dq.back().y >= cur) dq.pop_back();
        while (dq.size() >= 2 and getintersect(dq[dq.size() - 2], curline) <= getintersect(dq[dq.size() - 2], dq.back())) dq.pop_back();
        if (dq.empty() or dq.back().m > f[i]) dq.push_back(Line(f[i], cur));
    }

    cout << ans << "\n";

	return 0;
}
