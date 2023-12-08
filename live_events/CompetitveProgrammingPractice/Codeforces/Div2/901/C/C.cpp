#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int L = 30;

int t;

bool works(int& val) {
    for (int i = 0; i < L; i++) {
        if ((1 << i) == val) {
            val = i;
            return true;
        }
    }
    return false;
}

void subcase() {
    int n, m, g, og;
    ll ans = 0;
    cin >> n >> m;
    og = m;
    g = gcd(n, m);
    n /= g;
    m /= g;
    if (not works(m)) {
        cout << "-1\n";
        return;
    }
    while (m > 0) {
        ans += (ll) ((1 << m) - 1) * (og / (1 << m));
        n--;
        while (n % 2 == 0 and m > 0) {
            n /= 2;
            m--;
        }
    }
    cout << ans << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
