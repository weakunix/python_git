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

const int N = 1e6 + 1, K = 100;

int n, k, p[K];
bool ans[N];

int main() {
    memset(ans, false, sizeof(ans));

    cin >> n >> k;
    for (int i = 0; i < k; i++) cin >> p[i];
    for (int i = 0; i < n; i++) {
        if (ans[i]) continue;
        for (int j = 0; j < k; j++) {
            if (i + p[j] <= n) ans[i + p[j]] = true;
        }
    }
    for (int i = 1; i <= n; i++) cout << (ans[i] ? 'W' : 'L');
    cout << "\n";
	return 0;
}
