#include <iostream>
#include <string>
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
    int a, b;
    cin >> a >> b;
    if ((a + b) % 3 != 0) {
        cout << "NO\n";
        return;
    }
    if (a > b) swap(a, b);
    if (b - a > a) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
