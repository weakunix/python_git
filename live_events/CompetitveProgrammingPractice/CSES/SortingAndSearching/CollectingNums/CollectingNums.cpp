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

int n, ans = 0;
vector<int> idx;

int main() {
    cin >> n;
    idx.resize(n + 1, 1e9);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        idx[cur] = i;
    }
    for (int i = 1; i <= n; i++) ans += (idx[i] <= idx[i - 1]);
    cout << ans << "\n";
	return 0;
}
