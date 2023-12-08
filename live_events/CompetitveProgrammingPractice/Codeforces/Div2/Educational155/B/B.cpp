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

const int N = 3e5;

int t;

void subcase() {
    int n, a[N], b[N], mina = 1e9, minb = 1e9;
    ll ansa = 0, ansb = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mina = min(a[i], mina);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        minb = min(b[i], minb);
    }

    for (int i = 0; i < n; i++) {
        ansa += a[i] + minb;
        ansb += b[i] + mina;
    }
    
    cout << min(ansa, ansb) << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
