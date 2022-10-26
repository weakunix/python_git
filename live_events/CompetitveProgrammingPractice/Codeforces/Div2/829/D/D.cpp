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

int main() {
    int n, x, cur = 0;
    cin >> n >> x;
    vector<int> factcount(x + 1);
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        factcount[val]++;
    }
    for (int i = 2; i <= x; i++) {
        cur += factcount[i - 1];
        if (cur % i != 0) {
            cout << "No\n";
            return 0;
        }
        cur /= i;
    }
    cout << "Yes\n";
	return 0;
}
