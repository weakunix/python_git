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

const int N = 2e5;

int n, cnt[N], ans = 0;

int main() {
    for (int i = 0; i < N; i++) {
        cnt[i] = 0;
        for (int j = 2; i / j > 0; j <<= 1) cnt[i] += i / j;
    }

    cin >> n;
    n--;
    for (int i = 0; i <= n; i++) {
        int cur;
        cin >> cur;
        if (cnt[n] == cnt[i] + cnt[n - i]) ans ^= cur;
    }

    cout << ans << "\n";

	return 0;
}
