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
    int n;
    string a, b, res;
    cin >> n >> a >> b;
    vector<simps> ans;
    for (int i = 0; i < n; i++) {
        if (a[i] == '1') ans.push_back({i + 1, i + 1});
    }
    if (ans.size() % 2 == 0) res.resize(n, '0');
    else res.resize(n, '1');
    for (const simps& s : ans) {
        if (ans.size() % 2 == 0) res[s.first - 1] = '1';
        else res[s.first - 1] = '0';
    }
    if (res != b) {
        ans.push_back({1, 1});
        ans.push_back({2, n});
        ans.push_back({1, n});
        for (int i = 0; i < n; i++) {
            if (res[i] == '0') res[i] = '1';
            else res[i] = '0';
        }
        if (res != b) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n" << ans.size() << "\n";
    for (const simps& s : ans) cout << s.first << " " << s.second << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
