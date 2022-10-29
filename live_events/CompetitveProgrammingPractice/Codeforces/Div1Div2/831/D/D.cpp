#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n, m, k, next;
    set<int> seen;
    cin >> n >> m >> k;
    next = k;
    vector<int> arr(k);
    for (int i = 0; i < k; i++) cin >> arr[i];
    for (int i : arr) {
        seen.insert(i);
        if (seen.size() == n * m - 2) {
            cout << "TIDAK\n";
            return;
        }
        while (seen.count(next) > 0) {
            seen.erase(next);
            next--;
        }
        if (next == 0) {
            cout << "YA\n";
            return;
        }
    }
    assert(false);
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
