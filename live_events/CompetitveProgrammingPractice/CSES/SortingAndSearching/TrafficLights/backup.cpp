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
multiset<int> alllens;
map<int, int> lens;

int main() {
    cin >> m >> n;
    alllens.insert(m);
    lens[m] = m;
    for (int i = 0; i < n; i++) {
        int cur, nxt;
        cin >> cur;
        nxt = lens.upper_bound(cur)->first;
        alllens.erase(alllens.find(lens[nxt]));
        lens[cur] = lens[nxt] - (nxt - cur);
        lens[nxt] = nxt - cur;
        alllens.insert(lens[cur]);
        alllens.insert(lens[nxt]);
        cout << *alllens.rbegin() << " ";
    }
	return 0;
}
