#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 5000, C = 1e4;

int n;
ll ans = 0;
pair<pt, pt> rect[N];

bool cmp(pair<pt, pt>& a, pair<pt, pt>& b) {
    return a.first.x < b.first.x;
}

void cinpt(pt& p) {
	int curx, cury;
	cin >> curx >> cury;
	p = {curx, cury};
	return;
}

ll cross(pt a, pt b) {
	return (conj(a) * b).y;
}

void rotpt(pt& p) {
    p = {-p.y, p.x};
    return;
}

ll leftperim() {
    ll res = 0;
    set<simps> rng;
    for (int i = 0; i < n; i++) {
        pt l = rect[i].first, r = rect[i].second;
        while (rng.size() and rng.begin()->first < l.x) rng.erase(rng.begin());

        vector<ll> pfx(2 * C + 2);
        for (const simps& s : rng) {
            int curl = rect[s.second].first.y, curr = rect[s.second].second.y;
            pfx[curl + C]++;
            pfx[curr + C]--;
        }

        for (int i = 0; i < r.y + C; i++) {
            if (i > 0) pfx[i] += pfx[i - 1];
            res += (i >= l.y + C and pfx[i] == 0);
        }

        rng.insert({r.x, i});
    }

    return res;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cinpt(rect[i].first);
        cinpt(rect[i].second);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            rotpt(rect[j].first);
            rotpt(rect[j].second);
            int cur = rect[j].first.x;
            rect[j].first = {rect[j].second.x, rect[j].first.y};
            rect[j].second = {cur, rect[j].second.y};
        }
        sort(rect, rect + n, cmp);

        ans += leftperim();
    }

    cout << ans << "\n";
    
	return 0;
}
