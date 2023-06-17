#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n;
ll mxelem = -1e9, cursm = 0, ans = 0;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        mxelem = max(cur, mxelem);
        cursm += cur;
        cursm = max((ll) 0, cursm);
        ans = max(cursm, ans);
    }
    cout << (mxelem < 0 ? mxelem : ans) << "\n";
	return 0;
}
