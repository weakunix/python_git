#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

int t;

void subcase() {
    int n, m, k, mna = 1e9, mnb = 1e9, mxa = 0, mxb = 0;
    ll sma = 0;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        sma += cur;
        mna = min(cur, mna);
        mxa = max(cur, mxa);
    }
    for (int i = 0; i < m; i++) {
        int cur;
        cin >> cur;
        mnb = min(cur, mnb);
        mxb = max(cur, mxb);
    }
    if (mna < mxb) sma += mxb - mna;
    if ((k - 1) % 2) {
        sma += min(mna, mnb) - max(mxa, mxb);
    }
    cout << sma << "\n";
    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
