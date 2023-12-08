#include <iostream>
#include <cstdio>
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

const int N = 3e6;

int n, k, arr[N], cnt = 0;

int main() {
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);

    memset(arr, 0, sizeof(arr));

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        for (int j = 0; j < y; j++) {
            b = (b + a) % n;
            arr[b] += x;
        }
    }

    for (int i = 0; i < n; i++) {
        cnt += arr[i];
        if (cnt > 0) cnt--;
    }

    for (int i = 0; i < n; i++) {
        if (cnt == 0 and arr[i] == 0) {
            cout << i << "\n";
            return 0;
        }
        cnt += arr[i] - 1;
    }

    assert(false);

	return 0;
}
