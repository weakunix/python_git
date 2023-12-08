#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <set>
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

const int N = 1e5 + 1;

int n, res[N], curidx = -1;
ll ans = 0;
simps arr[N];

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }

    if (n == 1) {
        cout << "0\n";
        return 0;
    }

    sort(arr, arr + n);

    res[0] = 0;
    for (int i = 0; i < n; i++) {
        curidx = max(arr[i].second, curidx);
        res[i + 1] = curidx - i;
    }

    for (int i = 0; i < n; i++) ans += max({res[i], res[i + 1], 1});

    cout << (ans ? ans : n) << "\n";

	return 0;
}
