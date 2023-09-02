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

int q;

int solve(int n, int k) {
    if (n == 1) return 1;
    if (n / 2 < k) {
        int cur = 2 * solve(n - n / 2, k - n / 2) - 1;
        if (n % 2 == 0) return cur;
        if (cur == 1) cur = n;
        else cur -= 2;
        return cur;
    }
    return 2 * k;
}

int main() {
    cin >> q;
    for (int i = 0; i < q; i++) {
        int n, k;
        cin >> n >> k;
        cout << solve(n, k) << "\n";
    }
	return 0;
}
