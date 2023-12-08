#include <iostream>
#include <string>
#include <cstring>
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

const int N = 2e5;

int n, k, arr[N], pfx[N], ans = 0;

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        pfx[i] = arr[i];
        if (i > 0) pfx[i] += pfx[i - 1];
    }

    for (int i = 0; i < min(n, k + 1); i++) ans = max(pfx[i] - pfx[0] + (k - i) * arr[i], ans);

    cout << ans << "\n";

	return 0;
}
