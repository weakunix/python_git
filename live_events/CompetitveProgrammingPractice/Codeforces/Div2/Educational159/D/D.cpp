#include <iostream>
#include <string>
#include <cstring>
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

const int N = 2e5 + 1;

int n, q;
simps arr[N];
map<simps, vector<int>> ord;

int main() {
    arr[0] = {0, 0};
    ord[arr[0]].push_back(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        arr[i] = arr[i - 1];
        if (c == 'U') arr[i].second++;
        else if (c == 'D') arr[i].second--;
        else if (c == 'R') arr[i].first++;
        else arr[i].first--;
        ord[arr[i]].push_back(i);
    }

    for (int i = 0; i < q; i++) {
        int x, y, l, r;
        cin >> x >> y >> l >> r;
        simps cur = {x, y};

        if (x == 0 and y == 0) {
            cout << "YES\n";
            continue;
        }

        if (ord.count(cur)) {
            if (lower_bound(all(ord[cur]), l) != ord[cur].begin()) {
                cout << "YES\n";
                continue;
            }
            if (upper_bound(all(ord[cur]), r) != ord[cur].end()) {
                cout << "YES\n";
                continue;
            }
        }

        cur = {arr[l - 1].first + arr[r].first - x, arr[l - 1].second + arr[r].second - y};

        if (ord.count(cur)) {
            auto it = lower_bound(all(ord[cur]), l - 1);
            if (it != ord[cur].end() and *it <= r) {
                cout << "YES\n";
                continue;
            }
        }

        cout << "NO\n";
    }

	return 0;
}
