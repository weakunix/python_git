#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
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

const int N = 1e5 + 3;

int n, k, pfx[8][N], ans = -1;
simps cows[N];
map<vector<int>, int> mp[1 << 8];

void fillmp() {
    vector<int> fillval(8);
    for (int i = 0; i < (1 << 8); i++) {
        if (__builtin_popcount(i) >= k) mp[i][fillval] = 1;
    }
    return;
}

int main() {

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> cows[i].first >> cows[i].second;
        cows[i].second--;
    }
    sort(cows + 1, cows + n + 1);
    
    fillmp();

    for (int i = 0; i < 8; i++) pfx[i][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 8; j++) pfx[j][i] = pfx[j][i - 1] + (cows[i].second == j);
    }

    for (int i = 1; i <= n; i++) {
        int msk = 0;

        for (int j = i; j > 0; j--) {
            int breed = cows[j].second;

            if (msk & (1 << breed)) continue;
            msk |= 1 << breed;
            if (__builtin_popcount(msk) < k) continue;

            int lowbit = 0;
            vector<int> cur(8);

            for (int l = msk & (-msk); l > 1; l /= 2) lowbit++;

            for (int l = 0; l < 8; l++) {
                if (msk & (1 << l)) cur[l] = pfx[l][i] - pfx[lowbit][i];
                else cur[l] = pfx[l][i];
            }
            
            if (mp[msk].count(cur)) ans = max(cows[i].first - cows[mp[msk][cur]].first, ans);
        }

        msk = 0;

        for (int j = i; j <= n; j++) {
            int breed = cows[j].second;

            if (msk & (1 << breed)) continue;
            msk |= 1 << breed;
            if (__builtin_popcount(msk) < k) continue;

            int lowbit = 0;
            vector<int> cur(8);
                
            for (int l = msk & (-msk); l > 1; l /= 2) lowbit++;

            for (int l = 0; l < 8; l++) {
                if (msk & (1 << l)) cur[l] = pfx[l][i] - pfx[lowbit][i];
                else cur[l] = pfx[l][i];
            }

            if (not mp[msk].count(cur)) mp[msk][cur] = i + 1;
        }
    }

    cout << ans << "\n";
	return 0;
}
