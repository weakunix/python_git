#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

int Subcase() {
    int n, minval, res = 0;
    cin >> n;
    vector<int> peels(n);
    for (int i = 0; i < n; i++) cin >> peels[i];
    minval = *min_element(all(peels));
    for (int i : peels) res += i / (2 * minval - 1) - (i % (2 * minval - 1) == 0);
    return res;
}

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) cout << Subcase() << "\n";
	return 0;
}
