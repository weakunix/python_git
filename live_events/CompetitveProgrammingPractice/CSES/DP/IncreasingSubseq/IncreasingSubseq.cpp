#include <iostream>
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

int n;
vector<int> ans;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur, idx;
        cin >> cur;
        idx = lower_bound(all(ans), cur) - ans.begin();
        if (idx == ans.size()) ans.push_back(cur);
        else ans[idx] = cur;
    }
    cout << ans.size() << "\n";
	return 0;
}
