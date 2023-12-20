#include <iostream>
#include <cstring>
#include <vector>
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

int n, cur = 0, ans = 0;
set<int> seen;

int main() {
    seen.insert(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        cur ^= val;

        int l = 0, r = 1 << 30;
        for (int j = 29; j >= 0; j--) {
            int mid = l + (r - l) / 2;
            if ((1 << j) & cur) {
                auto it = seen.lower_bound(l);
                if (*it < mid) r = mid;
                else l = mid;
            }
            else {
                auto it = seen.lower_bound(mid);
                if (it != seen.end() and *it < r) l = mid;
                else r = mid;
            }
        }

        assert(l + 1 == r and seen.count(l));

        ans = max(cur ^ l, ans);

        seen.insert(cur);
    }

    cout << ans << "\n";

	return 0;
}
