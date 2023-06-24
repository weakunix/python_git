#include <iostream>
#include <vector>
#include <utility>
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

const int modval = 1e9 + 7;

int t;
vector<ll> same(1e6 + 1, 1), diff(1e6 + 1, 1);

int main() {
    cin >> t;
    for (int i = 2; i <= 1e6; i++) {
        same[i] = (same[i - 1] * 2 + diff[i - 1]) % modval;
        diff[i] = (same[i - 1] + diff[i - 1] * 4) % modval;
    }
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        cout << (same[n] + diff[n]) % modval << "\n";
    }
	return 0;
}
