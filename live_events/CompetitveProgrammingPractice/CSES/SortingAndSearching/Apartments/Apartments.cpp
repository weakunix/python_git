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

int n, m, k, ans = 0;
vector<int> a, b;

int main() {
    cin >> n >> m >> k;
    a.resize(n);
    b.resize(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(all(a));
    sort(all(b));
    while (not a.empty() and not b.empty()) {
        if (abs(a.back() - b.back()) <= k) {
            ans++;
            a.pop_back();
            b.pop_back();
            continue;
        }
        if (a.back() > b.back()) a.pop_back();
        else b.pop_back();
    }
    cout << ans << "\n";
	return 0;
}
