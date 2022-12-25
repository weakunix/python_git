#include <iostream>
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

int n, q;
vector<int> hgt;
vector<set<simps>> arr;

bool slopecmp(simps a, simps b) {
    return ((ll) a.second * b.first <= (ll) b.second * a.first);
}

int main() {
    cin >> n;
    hgt.resize(n);
    arr.resize(n - 1);
    for (int i = 0; i < n; i++) cin >> hgt[i];
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            simps cur = {j - i, hgt[j] - hgt[i]};
            if (arr[i].empty()) {
                arr[i].insert(cur);
                continue;
            }
            auto it = arr[i].end();
            it--;
            if (slopecmp(*it, cur)) arr[i].insert(cur);
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b, res = 0;
        cin >> a >> b;
        a--;
        hgt[a] += b;
        for (int j = 0; j < a; j++) {
            simps cur = {a - j, hgt[a] - hgt[j]};
            auto it = arr[j].upper_bound(cur);
            if (it != arr[j].begin()) {
                it--;
                if (not slopecmp(*it, cur)) continue;
                if (it->first == cur.first) arr[j].erase(*it);
            }
            arr[j].insert(cur);
            it = arr[j].upper_bound(cur);
            while (it != arr[j].end() and not slopecmp(cur, *it)) {
                arr[j].erase(*it);
                it = arr[j].upper_bound(cur);
            }
        }
        arr[a].clear();
        for (int j = a + 1; j < n; j++) {
            simps cur = {j - a, hgt[j] - hgt[a]};
            if (arr[a].empty()) {
                arr[a].insert(cur);
                continue;
            }
            auto it = arr[a].end();
            it--;
            if (slopecmp(*it, cur)) arr[a].insert(cur);
        }
        for (int i = 0; i < n - 1; i++) res += arr[i].size();
        cout << res << "\n";
    }
	return 0;
}
