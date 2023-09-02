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

const int modval = 1e9 + 7;

int n, m;
ll finalans = 0;
vector<ll> ans;

int main() {
    cin >> n >> m;
    assert(n <= 16);
    ans.resize(1 << n, 1);
    for (int i = 0; i < m; i++) {
        string s;
        vector<int> seq = {0};
        cin >> s;
        for (char c : s) {
            if (c == 'R') seq.push_back(0);
            else if (c == '0') seq.back() = 2;
            else if (c == '1') seq.back() = 3;
            else seq.back() ^= 1;
        }
        for (int j = 1; j < (1 << n); j++) {
            int last = 0;
            for (int k = n - 1; k >= 0; k--) {
                if ((1 << k) & j) {
                    last = k;
                    break;
                }
            }
            if (last + seq.size() > n) continue;
            ll curans = 1;
            for (int l = 0; l < n; l++) {
                vector<bool> use(4);
                for (int k = 0; k < n; k++) {
                    if ((1 << k) & j) {
                        if (l >= k and l < k + seq.size()) {
                            use[seq[l - k]] = true;
                        }
                        else use[0] = true;
                    }
                }
                if ((use[0] and use[1]) or (use[2] and use[3])) continue;
                if ((use[0] or use[1]) and (use[2] or use[3])) curans = (curans * 2) % modval;
                else curans = (curans * 3) % modval;
            }
            ans[j] = (ans[j] * curans) % modval;
        }
    }
    for (int i = 1; i < (1 << n); i++) {
        if (__builtin_parity(i)) finalans = (finalans + ans[i]) % modval;
        else finalans = (finalans + modval - ans[i]) % modval;
    }
    cout << finalans << "\n";
	return 0;
}
