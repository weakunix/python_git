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
    int n, m;
    cin >> n >> m;
    if (m == 1) {
        for (int i = 0; i <= n; i++) cout << "0\n";
        return;
    }
    cout << min(n + 1, m) << "\n";
    while (n >= m) {
        for (int i = 0; i < m; i++) cout << i << " ";
        cout << "\n";
        n--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << (i + j) % m << " ";
        cout << "\n";
    }
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
