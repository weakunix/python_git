#include <iostream>
#include <string>
#include <cstring>
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

int a, b, n, prv = 0, mxx = 0, mxy = 0;

int main() {
    cin >> a >> b >> n;

    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        mxx = max(cur - prv, mxx);
        prv = cur;
    }
    mxx = max(a - prv, mxx);

    cin >> n;
    prv = 0;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        mxy = max(cur - prv, mxy);
        prv = cur;
    }
    mxy = max(b - prv, mxy);

    cout << mxx * mxy << "\n";

	return 0;
}
