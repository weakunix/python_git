#include <iostream>
#include <vector>
#include <utility>
#include <map>
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

int n, cur = 0, ans = 0;
map<int, int> cnt;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int st, en;
        cin >> st >> en;
        cnt[st]++;
        cnt[en]--;
    }
    for (auto& u : cnt) {
        cur += u.second;
        ans = max(cur, ans);
    }
    cout << ans << "\n";
	return 0;
}
