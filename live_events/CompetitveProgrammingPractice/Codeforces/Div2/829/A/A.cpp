#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, count = 0;
    string s;
    cin >> n >> s;
    if (s[0] == 'A') {
        cout << "No\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == 'Q') count++;
        else count = max(count - 1, 0);
    }
	if (count <= 0) cout << "YES\n";
    else cout << "NO\n";
    return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
