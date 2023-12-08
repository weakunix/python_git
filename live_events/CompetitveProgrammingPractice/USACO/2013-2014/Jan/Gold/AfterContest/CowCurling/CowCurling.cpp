#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
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

const int N = 5e4;

int n;
simps l, r;
vector<int> hulltop, hullbot;
pt teama[N], teamb[N];

ll cross(pt a, pt b) {
    return (conj(a) * b).y;
}

bool cmp(pt a, pt b) {
    return a.x == b.x ? (a.y < b.y) : (a.x < b.x);
}

void genhull(pt (&team)[N]) {
    int sz = 2;
    hullbot = {0, 1};
    for (int i = 2; i < n; i++) {
        while (hullbot.size() > 1 and cross(team[hullbot[sz - 1]] - team[hullbot[sz - 2]], team[i] - team[hullbot[sz - 2]]) <= 0) {
            hullbot.pop_back();
            sz--;
        }
        hullbot.push_back(i);
        sz++;
    }
    if (team[hullbot[sz - 1]].x == team[hullbot[sz - 2]].x) {
        hullbot.pop_back();
        r = {team[hullbot[sz - 2]].y, team[hullbot[sz - 1]].y};
        assert(r.first < r.second);
    }
    else r = {team[hullbot[sz - 1]].y, team[hullbot[sz - 1]].y};

    sz = 2;
    hulltop = {n - 1, n - 2};
    for (int i = n - 3; i >= 0; i--) {
        while (hulltop.size() > 1 and cross(team[hulltop[sz - 1]] - team[hulltop[sz - 2]], team[i] - team[hulltop[sz - 2]]) <= 0) {
            hulltop.pop_back();
            sz--;
        }
        hulltop.push_back(i);
        sz++;
    }
    if (team[hulltop[sz - 1]].x == team[hulltop[sz - 2]].x) {
        hulltop.pop_back();
        l = {team[hulltop[sz - 1]].y, team[hulltop[sz - 2]].y};
        assert(l.first < l.second);
    }
    else l = {team[hulltop[sz - 1]].y, team[hulltop[sz - 1]].y};
    reverse(all(hulltop));

    /*
    for (int i : hullbot) cout << team[i] << " ";
    cout << "\n";
    for (int i : hulltop) cout << team[i] << " ";
    cout << "\n";
    *///

    return;
}

int getans(pt (&curpts)[N], pt (&hullpts)[N]) {
    int res = 0;
    vector<int> topx, botx;

    for (int i : hullbot) botx.push_back(hullpts[i].x);
    for (int i : hulltop) topx.push_back(hullpts[i].x);

    for (int i = 0; i < n; i++) {
        if (curpts[i].x < hullpts[0].x or curpts[i].x > hullpts[n - 1].x) continue;
        if (curpts[i].x == hullpts[0].x) {
            if (curpts[i].y >= l.first and curpts[i].y <= l.second) res++;
            continue;
        }
        if (curpts[i].x == hullpts[n - 1].x) {
            if (curpts[i].y >= r.first and curpts[i].y <= r.second) res++;
            continue;
        }

        int idx = lower_bound(all(botx), curpts[i].x) - botx.begin();
        if (idx > 0) idx--;
        if (cross(hullpts[hullbot[idx]] - curpts[i], hullpts[hullbot[idx + 1]] - curpts[i]) < 0) continue;

        idx = lower_bound(all(topx), curpts[i].x) - topx.begin();
        if (idx > 0) idx--;
        if (cross(hullpts[hulltop[idx]] - curpts[i], hullpts[hulltop[idx + 1]] - curpts[i]) < 0) res++;
    }

    return res;
}

int main() {
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int curx, cury;
        cin >> curx >> cury;
        teama[i] = {curx, cury};
    }
    for (int i = 0; i < n; i++) {
        int curx, cury;
        cin >> curx >> cury;
        teamb[i] = {curx, cury};
    }

    sort(teama, teama + n, cmp);
    sort(teamb, teamb + n, cmp);

    genhull(teama);
    cout << getans(teamb, teama) << " ";

    genhull(teamb);
    cout << getans(teama, teamb) << "\n";

	return 0;
}
