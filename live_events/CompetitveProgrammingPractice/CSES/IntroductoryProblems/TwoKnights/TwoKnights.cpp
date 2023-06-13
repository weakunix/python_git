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

int n;

void solve(ll k) {
    if (k == 1) {
        cout << "0\n";
        return;
    }
    if (k == 2) {
        cout << "6\n";
        return;
    }
    cout << k * k * (k * k - 1) / 2 - 4 * (k - 1) * (k - 2) << "\n";
    return;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) solve(i);
	return 0;
}
