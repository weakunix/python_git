#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef __int128 ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 5e4;

struct Frac {
    ll num, den;

    Frac(ll numm = 0, ll denn = 1) {
        num = numm;
        den = denn;

        if (den < 0) {
            num = -num;
            den = -den;
        }

        return;
    }
};

bool operator<(Frac a, Frac b) {
    if (a.num < 0 and b.num > 0) return true;
    if (a.num > 0 and b.num < 0) return false;
    if (a.num < 0 and b.num < 0) {
        a.num = -a.num;
        b.num = -b.num;
        swap(a, b);
    }
    return a.num * b.den < a.den * b.num;
}

struct Line {
    ll slope, yint;

    Line(ll m, ll b) {
        slope = m;
        yint = b;
        return;
    }

    Frac eval(Frac x) const {
        return Frac(slope * x.num + yint * x.den, x.den);
    }
};

bool operator<(Line a, Line b) {
    return a.slope == b.slope ? a.yint > b.yint : a.slope < b.slope;
}

Frac getintersect(Line a, Line b) {
    return Frac(b.yint - a.yint, a.slope - b.slope);
}

int n;
Frac arr[N], l[N], x(0, 0);
vector<int> ans;
set<Line> cht;

//TEMP STUFF
Frac ogx;

auto getprv(Line cur) {
    auto it = cht.upper_bound(cur);
    if (it == cht.begin()) return cht.end();
    it--;
    return it;
}

auto getnxt(Line cur) {
    return cht.upper_bound(cur);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = Frac(a, b);
        x.num += a;
        x.den += b;
    }
    sort(arr, arr + n);
    ogx = x; //TEMP

    for (int i = 0; i < n; i++) {
        bool works = true;
        Line cur(-arr[i].den, arr[i].num);

        x.num -= arr[i].num;
        x.den -= arr[i].den;

        auto it1 = getprv(cur);
        if (it1 != cht.end() and it1->slope == cur.slope) {
            if (it1->yint > cur.yint) works = false;
            else cht.erase(it1);
        }

        auto it2 = getnxt(cur);
        if (it2 != cht.end() and it2->slope == cur.slope) {
            if (it2->yint > cur.yint) works = false;
            else cht.erase(it2);
        }

        it1 = getprv(cur);
        it2 = getnxt(cur);
        if (it1 != cht.end() and it2 != cht.end()) {
            if (not (getintersect(*it1, cur) < getintersect(*it1, *it2))) works = false;
        }

        if (works) {
            while (true) {
                it2 = getprv(cur);
                if (it2 == cht.end()) break;
                it1 = getprv(*it2);
                if (it1 == cht.end()) break;
            
                if (getintersect(*it1, *it2) < getintersect(*it1, cur)) break;
                cht.erase(it2);
            }

            while (true) {
                it1 = getnxt(cur);
                if (it1 == cht.end()) break;
                it2 = getnxt(*it1);
                if (it2 == cht.end()) break;
            
                if (getintersect(cur, *it1) < getintersect(cur, *it2)) break;
                cht.erase(it1);
            }

            cht.insert(cur);
        }

        while (cht.size() >= 2) {
            it1 = cht.begin();
            it2 = cht.begin();
            it2++;

            if (x < getintersect(*it1, *it2)) break;
            cht.erase(it1);
        }

        assert(cht.size());

        l[i] = cht.begin()->eval(x);
    }

    x = ogx;
    for (int i = 0; i < n; i++) {
        x.num -= arr[i].num;
        x.den -= arr[i].den;

        Frac mn(1e18, 1), mx(-1e18, 1);

        for (int j = 0; j <= i; j++) {
            Frac cur(arr[j].num * x.den - arr[j].den * x.num, x.den);
            if (mx < cur) mx = cur;
        }
        for (int j = i + 1; j < n; j++) {
            Frac cur(arr[j].num * x.den - arr[j].den * x.num, x.den);
            if (cur < mn) mn = cur;
        }

        if (mn < l[i]) ans.push_back(i + 1);
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";

	return 0;
}
