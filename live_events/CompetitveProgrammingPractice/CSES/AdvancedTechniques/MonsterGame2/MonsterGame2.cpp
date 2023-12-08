#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

struct Frac {
    ll num, den;

    Frac(ll nnum = 0, ll dden = 0) {
        num = nnum;
        den = dden;
        if (den < 0) {
            den = -den;
            num = -num;
        }
        return;
    }
};

bool operator<(Frac a, Frac b) {
    if (a.num < 0 and b.num >= 0) return true;
    if (b.num < 0 and a.num >= 0) return false;

    if (a.num < 0 and b.num < 0) {
        swap(a, b);
        a.num = -a.num;
        b.num = -b.num;
    }
    return a.num * b.den < a.den * b.num;
}

bool operator>(Frac a, Frac b) {
    return b < a;
}

bool operator==(Frac a, Frac b) {
    return (not (a < b)) and (not (a > b));
}

struct Line {
    ll m, y;
    Frac lft;

    Line(ll mm = 0, ll yy = 0, ll num = 0, ll den = 0) {
        m = mm;
        y = yy;
        lft = Frac(num, den);
        return;
    }

    ll eval(ll x) {
        return m * x + y;
    }
};

Frac isect(Line a, Line b) {
    return Frac(a.y - b.y, b.m - a.m);
}

int n;
ll initf, lasts, s[N], f[N], ans;
Line line[N];

bool chtcmp(int a, int b) {
    return line[a].m == line[b].m ? a > b : line[a].m > line[b].m;
}

bool bestcmp(int a, int b) {
    return line[a].lft == line[b].lft ? a < b : line[a].lft < line[b].lft;
}

multiset<int, decltype(chtcmp)*> cht(chtcmp);
multiset<int, decltype(bestcmp)*> best(bestcmp);

int main() {
    cin >> n >> initf;
    for (int i = 1; i < n; i++) cin >> s[i];
    cin >> lasts;
    for (int i = 1; i < n; i++) cin >> f[i];

    ans = initf * lasts;
    line[0] = Line(initf, 0, 0, 1);
    cht.insert(0);
    best.insert(0);

    for (int i = 1; i < n; i++) {
        line[i].lft = Frac(s[i], 1);

        //query

        auto it = best.upper_bound(i);
        it--;
        ll cur = line[*it].eval(s[i]);
        ans = min(cur + f[i] * lasts, ans);

        line[i].m = f[i];
        line[i].y = cur;

        //parallel line and bad line

        int idx = cht.upper_bound(i) == cht.end() ? -1 : *cht.upper_bound(i);
        bool works = true;
        if (idx != -1 and line[idx].m == f[i]) {
            if (cur >= line[idx].y) works = false;
            else {
                cht.erase(idx);
                best.erase(idx);
            }
        }

        if (works) {
            auto it1 = cht.upper_bound(i), it2 = cht.upper_bound(i);
            it1--;
            if (it2 != cht.end()) if (works and isect(line[*it1], line[i]) > isect(line[*it1], line[*it2])) works = false;
        }
        
        if (not works) continue;

        //left

        while (true) {
            auto it1 = cht.upper_bound(i);
            if (it1 == cht.begin()) break;
            it1--;
            auto it2 = it1;
            if (it2 == cht.begin()) break;
            it2--;

            if (isect(line[*it2], line[*it1]) < isect(line[*it2], line[i])) break;
            int rem = *it1;
            cht.erase(rem);
            best.erase(rem);
        }

        //right

        while (true) {
            auto it1 = cht.upper_bound(i);
            if (it1 == cht.end()) break;
            auto it2 = it1;
            it2++;
            if (it2 == cht.end()) break;

            if (isect(line[*it1], line[i]) < isect(line[*it2], line[i])) break;
            int rem = *it1;
            cht.erase(rem);
            best.erase(rem);
        }

        //add
        auto it2 = cht.upper_bound(i);
        if (it2 != cht.end()) {
            best.erase(*it2);
            line[*it2].lft = isect(line[i], line[*it2]);
            best.insert(*it2);
        }
        it2--;
        line[i].lft = isect(line[i], line[*it2]);
        cht.insert(i);
        best.insert(i);
    }

    cout << ans << "\n";

	return 0;
}
