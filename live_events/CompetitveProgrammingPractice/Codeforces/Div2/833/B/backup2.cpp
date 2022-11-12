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
    int n, distinct = 0;
    ll ans = 0;
    string s;
    vector<int> cur(10);
    vector<vector<int>> idx(10);
    cin >> n >> s;
    for (int i = 0; i < n; i++) idx[s[i] - '0'].push_back(i);
    for (int i = 0; i < 10; i++) distinct += (not idx[i].empty());
    for (int i = 0; i < n; i++) {
        int minidx = n;
        for (int j = 0; j < 10; j++) {
            int curidx = cur[j] + distinct;
            if (curidx >= idx[j].size()) continue;
            minidx = min(idx[j][curidx], minidx);
        }
        cout << minidx - i << "\n";
        ans += minidx - i;
        cur[s[i] - '0']++;
    }
    cout << ans << "\n";
    return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
