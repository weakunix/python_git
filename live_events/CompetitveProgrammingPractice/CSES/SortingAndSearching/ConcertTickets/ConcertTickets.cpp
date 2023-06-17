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

int n, m;
multiset<int> tickets;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        tickets.insert(cur);
    }
    for (int i = 0; i < m; i++) {
        int cur;
        cin >> cur;
        auto it = tickets.upper_bound(cur);
        if (it == tickets.begin()) {
            cout << "-1\n";
            continue;
        }
        it--;
        cout << *it << "\n";
        tickets.erase(it);
    }
	return 0;
}
