#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void Subcase() {
    int n;
    string s, res;
    vector<int> a;
    map<int, char> m;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> s;
    for (int i = 0; i < n; i++) {
        int cur = a[i];
        if (m.count(cur) == 0) m[cur] = s[i];
        res += m[cur];
    }
    if (res == s) cout << "YES\n";
    else cout << "NO\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
