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

int t;

void subcase() {
    int n, k;
    cin >> n >> k;
    if ((n + k - 1) / k > k) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (int i = 1; i <= n; i += k) for (int j = min(i + k - 1, n); j >= i; j--) cout << j << " ";
    cout << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
