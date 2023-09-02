#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int MX = 2000;

int t, dp[MX];

void subcase() {
    int n;
    cin >> n;
    cout <<  (n >= 2000 or dp[n] ? "first\n" : "second\n");
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    memset(dp, 0, sizeof(dp));
    
    for (int i = 3; i < MX; i++) {
        set<int> seen;
        for (int j = 1; j <= (i - 1) / 2; j++) seen.insert(dp[j] ^ dp[i - j]);
        for (int j = 0; j < MX; j++) {
            if (seen.count(j)) continue;
            dp[i] = j;
            break;
        }
    }

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
