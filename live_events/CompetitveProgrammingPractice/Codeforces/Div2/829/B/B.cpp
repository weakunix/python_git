#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, res = 0;
    vector<int> resvect;
    cin >> n;
    for (int i = 1; i < n; i++) {
        vector<int> ord;
        vector<bool> visited(n);
        for (int j = i - 1; j >= 0; j--) {
            int cur = j;
            while (cur < n) {
                if (visited[cur]) break;
                ord.push_back(cur);
                visited[cur] = true;
                cur += i;
            }
        }
        int curres = 1e9;
        if (ord.size() < n) continue;
        for (int i = 0; i < n - 1; i++) curres = min(abs(ord[i] - ord[i + 1]), curres);
        if (curres > res) {
            res = curres;
            resvect = ord;
        }
    }
    for (int i : resvect) cout << i + 1 << " ";
    cout << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
