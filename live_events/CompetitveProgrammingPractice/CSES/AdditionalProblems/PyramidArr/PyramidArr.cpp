#include <iostream>
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

const int N = 2e5 + 1;

int n, bit[N];
ll ans = 0;
simps arr[N];

void setbit(int idx) {
    for (; idx <= n; idx += idx & (-idx)) bit[idx]++;
    return;
}

int getbit(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

int main() {
    memset(bit, 0, sizeof(bit));

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr + 1, arr + n + 1, greater<simps>());

    for (int i = 1; i <= n; i++) {
        int cur = arr[i].second, res = getbit(cur);
        ans += min(res, i - res - 1);
        setbit(cur);
    }

    cout << ans << "\n";

	return 0;
}
