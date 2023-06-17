#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
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

int n, ans = 0;
queue<int> q;
set<int> seen;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        while (seen.count(cur) > 0) {
            seen.erase(q.front());
            q.pop();
        }
        q.push(cur);
        seen.insert(cur);
        ans = max((int) q.size(), ans);
    }
    cout << ans << "\n";
	return 0;
}
