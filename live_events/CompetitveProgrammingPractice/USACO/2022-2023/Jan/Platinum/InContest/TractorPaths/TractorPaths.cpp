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

int n, q, l = 0, r = 0;
vector<simps> ranges;
vector<int> mx, special;

int main() {
    cin >> n >> q;
    ranges.resize(n);
    for (int i = 0; i < 2 * n; i++) {
        char c;
        cin >> c;
        if (c == 'L') {
            ranges[l].first = i;
            l++;
        }
        else {
            ranges[r].second = i;
            r++;
        }
    }
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '1') special.push_back(i);
    }
    for (int i = 0; i < n; i++) mx.push_back(lower_bound(all(ranges), make_pair(ranges[i].second, -1)) - ranges.begin());
    for (int i = 0; i < q; i++) {
        int a, b, ans = 0;
        cin >> a >> b;
        a--;
        b--;
        int cur = a, cnt = 0;
        cur = mx[cur];
        while (cur < b) {
            cnt++;
            cur = mx[cur];
        }
        for (int j : special) {
            int blah = a, cnttt = 0;
            blah = mx[blah];
            while (blah < j) {
                cnttt++;
                blah = mx[blah];
            }
            if (cnttt == cnt) ans++;
        }
        cout << ans << "\n";
    }
	return 0;
}
