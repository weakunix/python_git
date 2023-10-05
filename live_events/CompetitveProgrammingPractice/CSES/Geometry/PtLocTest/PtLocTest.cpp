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
        pt a, b, c;
        cinpt(a); cinpt(b); cinpt(c);
        ll res = cross(b - a, c - a);
        if (res == 0) cout << "TOUCH\n";
        else cout << (res < 0 ? "RIGHT\n" : "LEFT\n");
    }
	return 0;
}
