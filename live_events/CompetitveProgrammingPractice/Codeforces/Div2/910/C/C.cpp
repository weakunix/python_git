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
    int n, m, k, l;
    cin >> n >> m >> k;
    l = n + m - 2;

    if (l % 2 != k % 2 or k < l) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    if (k == l + 2) {
        for (int i = 0; i < m - 1; i++) cout << (i % 2 ? "R " : "B ");
        cout << "\n";
        for (int i = 1; i < n; i++) {
            for (int i = 0; i < m - 1; i++) cout << "R ";
            cout << "\n";
        }

        bool cur = m % 2;
        for (int i = 0; i < n - 1; i++) {
            cur = not cur;
            for (int i = 0; i < m; i++) cout << (cur ? "B " : "R ");
            cout << "\n";
        }

        return;
    }

    for (int i = 0; i < m - 1; i++) cout << (i % 2 ? "R " : "B ");
    cout << "\n";
    for (int i = 0; i < m - 1; i++) cout << (i % 2 ? "R " : "B ");
    cout << "\n";
    for (int i = 2; i < n; i++) {
        for (int i = 0; i < m - 1; i++) cout << "R ";
        cout << "\n";
    }

    bool cur = m % 2;
    cout << "R R B ";
    for (int i = 3; i < m; i++) cout << (cur ? "B " : "R ");
    cout << "\n";
    for (int i = 1; i < n - 1; i++) {
        cur = not cur;
        for (int i = 0; i < m; i++) cout << (cur ? "B " : "R ");
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
