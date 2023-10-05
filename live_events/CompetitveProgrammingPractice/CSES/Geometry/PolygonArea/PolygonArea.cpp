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

int n;
pt firstpt, lastpt;
ll ans = 0;

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
    cinpt(firstpt);
    lastpt = firstpt;
    for (int i = 1; i < n; i++) {
        pt curpt;
        cinpt(curpt);
        ans += cross(lastpt, curpt);
        lastpt = curpt;
    }
    ans += cross(lastpt, firstpt);
    cout << abs(ans) << "\n";
	return 0;
}
