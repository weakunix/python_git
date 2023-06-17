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

int n;
multiset<int> ms;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        auto it = ms.upper_bound(cur);
        if (it != ms.end()) ms.erase(it);
        ms.insert(cur);
    }
    cout << ms.size() << "\n";
	return 0;
}
