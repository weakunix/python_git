#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <algorithm>
#include <numeric>
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

const int N = 1e5 + 1;

int n;
ll area = 0, boundary = 0;
pt arr[N];

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
    cin >> n;
    for (int i = 0; i < n; i++) cinpt(arr[i]);
    arr[n] = arr[0];

    for (int i = 0; i < n; i++) {
        pt l = arr[i], r = arr[i + 1];
        area += cross(l, r);
        if (l.x > r.x) swap(l, r);

        ll curx = abs(l.x - r.x), cury = abs(l.y - r.y);
        if (not curx) boundary += cury + 1;
        else if (not cury) boundary += curx + 1;
        else boundary += gcd(curx, cury) + 1;
    }

    boundary -= n;

    cout << (abs(area) + 2 - boundary) / 2 << " " << boundary << "\n";
	return 0;
}
