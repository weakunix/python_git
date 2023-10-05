#include <iostream>
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

int t;

void cinpt(pt& p) {
	int curx, cury;
	cin >> curx >> cury;
	p = {curx, cury};
	return;
}

ll cross(pt a, pt b) {
	return (conj(a) * b).y;
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        pt a, b, c, d;
        cinpt(a); cinpt(b); cinpt(c); cinpt(d);
        ll res1 = cross(b - a, c - a), res2 = cross(b - a, d - a);
        if ((res1 < 0 and res2 < 0) or (res1 > 0 and res2 > 0)) {
            cout << "NO\n";
            continue;
        }
        res1 = cross(d - c, a - c), res2 = cross(d - c, b - c);
        if ((res1 < 0 and res2 < 0) or (res1 > 0 and res2 > 0)) {
            cout << "NO\n";
            continue;
        }
        if (res1 == 0 and res2 == 0) {
            if (min({a.x, b.x, c.x, d.x}) == max({a.x, b.x, c.x, d.x})) {
                if (a.y > b.y) swap(a, b);
                if (c.y > d.y) swap(c, d);
                if (a.y > d.y or c.y > b.y) {
                    cout << "NO\n";
                    continue;
                }
            }
            else {
                if (a.x > b.x) swap(a, b);
                if (c.x > d.x) swap(c, d);
                if (a.x > d.x or c.x > b.x) {
                    cout << "NO\n";
                    continue;
                }
            }
        }
        cout << "YES\n";
    }
	return 0;
}
