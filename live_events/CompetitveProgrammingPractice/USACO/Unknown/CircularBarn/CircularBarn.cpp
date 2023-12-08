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

const int N = 1001;

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

double isect(Line a, Line b) {
    return (double) (a.y - b.y) / (b.m - a.m);
}

struct ConvHullTrick {
    deque<Line> dq;

    ConvHullTrick() {
        return;
    }

    ll getmn(ll x) {
        assert(dq.size());
        while (dq.size() >= 2 and dq[0].eval(x) >= dq[1].eval(x)) dq.pop_front();
        return dq[0].eval(x);
    }

    void addline(Line l) {
        while (dq.size() and dq.back().y >= l.y) dq.pop_back();
        while (dq.size() >= 2 and isect(l, dq[dq.size() - 2]) < isect(dq.back(), dq[dq.size() - 2])) dq.pop_back();
        dq.push_back(l);
        return;
    }
};

int n, k;
ll arr[2 * N], pfx1[2 * N], pfx2[2 * N], ans = 1e18; //pfx1: sum(i * ai), pfx2: sum(ai)

ll cost(int l, int r) {
    assert(r > l);
    return pfx1[r - 1] - pfx1[l] - l * (pfx2[r - 1] - pfx2[l]);
}

void calc(int st) {
    vector<vector<ll>> dp(n + 1, vector<ll>(k, 1e18));
    vector<ConvHullTrick> cht(k);

    dp[st][0] = 0;
    cht[0].addline(Line(-st, st * pfx2[st] - pfx1[st]));

    for (int i = st + 1; i <= n; i++) {
        for (int j = 1; j < min(i - st + 1, k); j++) {
            dp[i][j] = cht[j - 1].getmn(pfx2[i - 1]) + pfx1[i - 1];
            cht[j].addline(Line(-i, dp[i][j] - pfx1[i] + i * pfx2[i]));
        }
    }

    for (int i = 1; i <= n; i++) ans = min(dp[i][k - 1] + cost(i, st + n), ans);
}

int main() {
    cin >> n >> k;
    if (k >= n) { //exception so that k < n
        cout << "0\n";
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arr[i + n] = arr[i];
    }

    pfx1[0] = 0;
    pfx2[0] = 0;
    for (int i = 1; i <= 2 * n; i++) {
        pfx1[i] = pfx1[i - 1] + i * arr[i];
        pfx2[i] = pfx2[i - 1] + arr[i];
    }

    for (int i = 1; i <= n; i++) calc(i);

    cout << ans << "\n";

	return 0;
}
