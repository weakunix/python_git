#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

ll Subcase() {
    int n;
    ll ans = 0;
    cin >> n;
    vector<int> a(n);
    vector<bool> can(n);
    vector<vector<int>> become(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        become[max(i + 1 - a[i], 0)].push_back(i);
    }
    int r = 0;
    for (int l = 0; l < n; l++) {
        for (int i : become[l]) can[i] = true;
        while (r < n and can[r]) r++;
        assert(r > l);
        ans += r - l;
    }
    return ans;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";
	return 0;
}
