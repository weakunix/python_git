#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>
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

const int N = 1e5 + 1, X = 1e5 + 3;
const ll modval = 1000000005721;

int n, k, pfx[8][N], ans = -1;
ll pw[8], smsks[N];
simps cows[N];

int main() {
    pw[0] = 1;
    for (int i = 1; i < 8; i++) pw[i] = pw[i - 1] * X % modval;

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> cows[i].first >> cows[i].second;
        cows[i].second--;
    }
    sort(cows + 1, cows + n + 1);

    for (int i = 0; i < 8; i++) pfx[i][0] = 0;
    for (int i = 1; i <= n; i++) {
        smsks[i] = 0;
        for (int j = 0; j < 8; j++) {
            pfx[j][i] = pfx[j][i - 1] + (cows[i].second == j);
            smsks[i] = (smsks[i] + pfx[j][i] * pw[j] % modval) % modval;
        }
    }

    for (int i = 0; i < (1 << 8); i++) {
        if (__builtin_popcount(i) < k) continue;

        int lowbit = 0;
        ll prv = 0, submsk = 0;
        unordered_map<ll, int> mp;
        
        for (int j = i & (-i); j > 1; j /= 2) lowbit++;
        for (int j = 0; j < 8; j++) {
            if ((1 << j) & i) submsk = (submsk + pw[j]) % modval;
        }

        for (int j = 1; j <= n; j++) {
            if (not mp.count(prv)) mp[prv] = cows[j].first;
            prv = (smsks[j] + modval - submsk * pfx[lowbit][j] % modval) % modval;
            if (mp.count(prv)) ans = max(cows[j].first - mp[prv], ans);
        }
    }
    cout << ans << "\n";
	return 0;
}
