#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <set>
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

const int N = 2e5;

bool cmpx(const pt& a, const pt& b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmpy(const pt& a, const pt& b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

int n, idx = 0;
ll ans;
pt arr[N];
set<pt, decltype(cmpy)*> s(cmpy);

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
    sort(arr, arr + n, cmpx);

    ans = norm(arr[0] - arr[1]);
    s.insert(arr[0]);
    s.insert(arr[1]);

    for (int i = 2; i < n; i++) {
        ll d = ceil(sqrt(ans));
        pt& cur = arr[i];
        while (idx < i and cur.x - arr[idx].x > d) {
            s.erase(arr[idx]);
            idx++;
        }
        
        auto l = s.lower_bound(pt(cur.x, cur.y - d)), r = s.upper_bound(pt(cur.x, cur.y + d));
        for (auto it = l; it != r; it++) ans = min(norm(*it - cur), ans);

        s.insert(arr[i]);
    }

    cout << ans << "\n";

	return 0;
}
