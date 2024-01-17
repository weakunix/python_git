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

const int N = 5001;

int n, a = 0, b = 0;
ll t, arra[N], arrb[N];
vector<vector<unordered_map<ll, ll>>> dp;

ll getdp(int aidx, int bidx, ll curt) {
    if (aidx == a and bidx == b) dp[aidx][bidx][curt] = 0;
    if (dp[aidx][bidx].count(curt)) return dp[aidx][bidx][curt];

    ll curdelay = 0;
    dp[aidx][bidx][curt] = 1e18;
    
    for (int i = aidx; i < a; i++) {
        curdelay += max(curt - arra[i], (ll) 0);
        dp[aidx][bidx][curt] = min(getdp(i + 1, bidx, max(curt, arra[i]) + t) + curdelay, dp[aidx][bidx][curt]);
    }

    curdelay = 0;
    for (int i = bidx; i < b; i++) {
        curdelay += max(curt - arrb[i], (ll) 0);
        dp[aidx][bidx][curt] = min(getdp(aidx, i + 1, max(curt, arrb[i]) + t) + curdelay, dp[aidx][bidx][curt]);
    }

    return dp[aidx][bidx][curt];
}

int main() {
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        char c;
        ll k;
        cin >> c >> k;
        if (c == 'A') {
            arra[a] = k;
            a++;
        }
        else {
            arrb[b] = k;
            b++;
        }
    }

    sort(arra, arra + a);
    sort(arrb, arrb + b);

    dp.resize(a + 1, vector<unordered_map<ll, ll>>(b + 1));

    cout << getdp(0, 0, 0) << "\n";

	return 0;
}
