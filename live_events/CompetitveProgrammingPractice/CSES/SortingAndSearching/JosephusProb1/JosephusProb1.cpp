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

int n, cur = 0;
set<int> rem;

void getnxt() {
    auto it = rem.upper_bound(cur);
    cur = (it == rem.end()) ? *rem.begin() : *it;
    return;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) rem.insert(i);
    while (not rem.empty()) {
        getnxt();
        getnxt();
        cout << cur << " ";
        rem.erase(cur);
    }
	return 0;
}
