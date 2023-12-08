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

const int N = 3001, K = 3000;

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
        while (dq.size() >= 2 and dq[0].eval(x) > dq[1].eval(x)) dq.pop_front();
        return dq[0].eval(x);
    }

    void addline(Line l) {
        while (dq.size() and dq.back().y > l.y) dq.pop_back();
        while (dq.size() >= 2 and isect(l, dq[dq.size() - 2]) <= isect(dq.back(), dq[dq.size() - 2])) dq.pop_back();
        dq.push_back(l);
        return;
    }
};

int n, k;
ll pfx[N];
ConvHullTrick cht[K];

int main() {
    pfx[0] = 0;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> pfx[i];
        pfx[i] += pfx[i - 1];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = min(i - 1, k - 1); j >= 0; j--) {
            ll cur = pfx[i] * pfx[i];
            if (j > 0) cur += cht[j - 1].getmn(pfx[i]);
            if (i == n and j == k - 1) {
                cout << cur << "\n";
                return 0;
            }
            cht[j].addline(Line(-2 * pfx[i], pfx[i] * pfx[i] + cur));
        }
    }

	return 0;
}
