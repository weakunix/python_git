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
    int n;
    cin >> n;
    if (n % 3 == 0) {
        if (n < 12) cout << "NO\n";
        else cout << "YES\n1 4 " << n - 5 << "\n";
    }
    else if (n % 3 == 1) {
        if (n < 7) cout << "NO\n";
        else cout << "YES\n1 4 " << n - 5 << "\n";
    }
    else {
        if (n < 8) cout << "NO\n";
        else cout << "YES\n2 5 " << n - 7 << "\n";
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
