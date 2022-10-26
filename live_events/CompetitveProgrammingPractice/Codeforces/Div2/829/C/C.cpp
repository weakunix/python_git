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
    int n, cursum = 0;
    cin >> n;
    vector<int> a(n);
    vector<simps> ans;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cursum += a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i + 1] * cursum > 0) {
            cursum -= 2 * a[i + 1];
            ans.push_back({i, i + 1});
            i++;
        }
        else ans.push_back({i, i});
    }
    if (cursum != 0) {
        cout << "-1\n";
        return;
    }
    cout << ans.size() << "\n";
    for (simps& s : ans) cout << s.first + 1 << " " << s.second + 1 << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
