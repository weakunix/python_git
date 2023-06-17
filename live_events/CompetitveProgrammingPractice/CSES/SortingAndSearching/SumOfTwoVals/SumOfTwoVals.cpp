#include <iostream>
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

int n, tar;
map<int, int> seen;

int main() {
    cin >> n >> tar;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        if (seen.count(tar - cur) > 0) {
            cout << i << " " << seen[tar - cur] << "\n";
            return 0;
        }
        seen[cur] = i;
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
