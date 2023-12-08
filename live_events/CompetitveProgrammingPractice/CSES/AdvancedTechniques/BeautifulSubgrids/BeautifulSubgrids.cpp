#pragma GCC target("popcnt")

#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
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

const int N = 3000;

int n;
ll ans = 0;
bitset<N> arr[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll cnt = (arr[i] & arr[j]).count();
            ans += cnt * (cnt - 1) / 2;
        }
    }

    cout << ans << "\n";

	return 0;
}
