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
const ll modval = 100000000069;

int n, k, pfx[8][N], ans = -1, cntcnt[N];
ll pw[8];
simps cows[N];

int main() {
    memset(cntcnt, 0, sizeof(cntcnt));
    cows[0] = {-1, 0};
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
        for (int j = 0; j < 8; j++) pfx[j][i] = pfx[j][i - 1] + (cows[i].second == j);
    }

    for (int i = 0; i < (1 << 8); i++) {
        int bitcnt = __builtin_popcount(i);
        if (bitcnt < k) continue;
        int cnt[8], common = 1;
        ll cur = 0, rem = 0;
        unordered_map<ll, int> pos;
        
        memset(cnt, 0, sizeof(cnt));
        cntcnt[0] = bitcnt;

        for (int j = 0; j < 8; j++) {
            if ((1 << j) & i) rem = (rem + pw[j]) % modval;
        }

        for (int j = 1; j <= n; j++) {
            int curpos = cows[j].first, breed = cows[j].second;
            if (not ((1 << breed) & i)) {
                for (int l : cnt) cntcnt[l] = 0;
                memset(cnt, 0, sizeof(cnt));
                pos.clear();
                cur = 0;
                common = 1;
                cntcnt[0] = bitcnt;
                continue;
            }
            if (pos.count(cur) == 0) pos[cur] = j - 1;
            cntcnt[cnt[breed]]--;
            cnt[breed]++;
            cntcnt[cnt[breed]]++;
            cur = (cur + pw[breed]) % modval;
           
            if (not cntcnt[common - 1]) {
                common++;
                cur = (cur + modval - rem) % modval;
            }

            if (not pos.count(cur)) continue;

            int prv = pos[cur];
            bool works = true;
            for (int l = 0; l < 8; l++) {
                if (not ((1 << l) & i)) continue;
                if (pfx[l][j] == pfx[l][prv]) {
                    works = false;
                    break;
                }
            }
            if (works) ans = max(curpos - cows[prv + 1].first, ans);
        }
        for (int l : cnt) cntcnt[l] = 0;
    }
    cout << ans << "\n";
	return 0;
}
