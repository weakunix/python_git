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

const int N = 1001, M = 1000;

int n, m;
bool inside[M], boundary[N];
pt poly[N], arr[M];

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
    memset(inside, false, sizeof(inside));
    memset(boundary, false, sizeof(boundary));

    cin >> n >> m;
    for (int i = 0; i < n; i++) cinpt(poly[i]);
    poly[n] = poly[0];
    for (int i = 0; i < m; i++) cinpt(arr[i]);

    for (int i = 0; i < n; i++) {
        pt l = poly[i], r = poly[i + 1];

        if (l.x == r.x) {
            if (l.y > r.y) swap(l, r);
            for (int j = 0; j < m; j++) {
                if (arr[j].x == l.x and (arr[j].y >= l.y and arr[j].y <= r.y)) boundary[j] = true;
            }
            continue;
        }

        if (l.x > r.x) swap(l, r);
        
        for (int j = 0; j < m; j++) {
            if (arr[j].x < l.x or arr[j].x >= r.x) continue;

            ll cur = cross(r - l, arr[j] - l);
            if (cur == 0) boundary[j] = true;
            else if (cur < 0) inside[j] = not inside[j];
        }
    }

    for (int i = 0; i < m; i++) cout << (boundary[i] ? "BOUNDARY\n" : (inside[i] ? "INSIDE\n" : "OUTSIDE\n"));

	return 0;
}
