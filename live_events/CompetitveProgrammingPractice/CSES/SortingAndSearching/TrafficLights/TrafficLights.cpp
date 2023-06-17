#include <iostream>
#include <vector>
#include <utility>
#include <set>
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

int m, n;
set<int> loc;
multiset<int> lens;

int main() {
    cin >> m >> n;
    loc.insert(0); loc.insert(m);
    lens.insert(m);
    for (int i = 0; i < n; i++) {
        int cur, prv, nxt;
        cin >> cur;
        auto it = loc.insert(cur).first;
        prv = *prev(it);
        nxt = *next(it);
        lens.erase(lens.find(nxt - prv));
        lens.insert(nxt - cur);
        lens.insert(cur - prv);
        cout << *lens.rbegin() << " ";
    }
	return 0;
}
