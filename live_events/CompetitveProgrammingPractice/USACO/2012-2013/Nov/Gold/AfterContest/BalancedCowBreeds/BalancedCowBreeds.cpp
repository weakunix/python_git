#include <iostream>
#include <cstdio>
#include <string>
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

const int modval = 2012;

int ans = 0;
string p;
map<simps, int> prv = {{{0, 0}, 1}};

int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
    cin >> p;
    for (int i = p.size() - 1; i >= 0; i--) {
        int val = (p[i] == '(' ? -1 : 1);
        map<simps, int> cur;
        for (auto& u : prv) {
            if (u.first.first + val >= 0) cur[{u.first.first + val, u.first.second}] = (cur[{u.first.first + val, u.first.second}] + u.second) % modval;
            if (u.first.second + val >= 0) cur[{u.first.first, u.first.second + val}] = (cur[{u.first.first, u.first.second + val}] + u.second) % modval;
        }
        swap(prv, cur);
    }
    for (auto& u : prv) ans = (ans + u.second) % modval;
    cout << ans << "\n";
	return 0;
}
