#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <complex>
#include <cassert>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ll> pt;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define x real()
#define y imag()

const int N = 1e5 + 2;

int n, sz = 1;
pt arr[N];
vector<int> hull;

ll cross(pt a, pt b) {
    return (conj(a) * b).y;
}

int main() {
    cin >> n;
    arr[0] = {0, 0};
    arr[n + 1] = {n + 1, 0};
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        arr[i] = {i, cur};
    }

    hull.push_back(n + 1);
    for (int i = n; i >= 0; i--) {
        while (sz > 1 and cross(arr[hull[sz - 1]] - arr[hull[sz - 2]], arr[i] - arr[hull[sz - 2]]) <= 0) {
            hull.pop_back();
            sz--;
        }
        hull.push_back(i);
        sz++;
    }

    for (int i = 1; i <= n; i++) {
        if (hull[sz - 2] == i) {
            hull.pop_back();
            sz--;
        }
        cout << (ll) (1e5 * ((ld) (i - hull[sz - 1]) / (hull[sz - 2] - hull[sz - 1]) * (arr[hull[sz - 2]].y - arr[hull[sz - 1]].y) + arr[hull[sz - 1]].y)) << "\n";
    }

	return 0;
}
