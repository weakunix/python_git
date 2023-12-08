#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
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
	ld curx, cury;
	cin >> curx >> cury;
	p = {curx, cury};
	return;
}


void subcase() {
    pt p, a, b;
    ld ans = 1e9;
    cinpt(p);
    cinpt(a);
    cinpt(b);
    ans = min(max(abs(a), abs(p - a)), max(abs(b), abs(p - b)));
    ans = min(max(abs(a - b) / 2, min(max(abs(a), abs(p - b)), max(abs(b), abs(p - a)))), ans);
    cout << fixed << setprecision(10) << ans << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
