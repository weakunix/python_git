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

int n, ans = 1;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) ans = (2 * ans) % modval;
    cout << ans << "\n";
	return 0;
}
