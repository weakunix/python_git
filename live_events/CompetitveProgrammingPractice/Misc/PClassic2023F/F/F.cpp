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

const int M = 13;

int n, fact[M], ans[M];

int main() {
    fact[0] = 1;
    for (int i = 1; i < 13; i++) fact[i] = fact[i - 1] * i;

    cin >> n;

    for (int i = 12; i > 0; i--) {
        int cur = n / fact[i];
        ans[i] = cur;
        n -= cur * fact[i];
    }

    bool lead0 = true;

    for (int i = 12; i > 0; i--) {
        if (lead0 and ans[i] == 0) continue;
        lead0 = false;
        //assert(ans[i] <= 10);
        
        if (ans[i] == 10) cout << 'A';
        else if (ans[i] == 11) cout << 'B';
        else cout << ans[i];
    }

    cout << "\n";

	return 0;
}
