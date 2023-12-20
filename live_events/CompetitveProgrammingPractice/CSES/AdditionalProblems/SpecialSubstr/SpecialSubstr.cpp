#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
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

const int N = 2e5;

int n, m, arr[N], seen = 0;
ll ans = 0;
string s;
map<char, int> mp;
map<vector<int>, int> pfxcnt;

int main() {
    cin >> s;
    n = s.size();

    for (int i = 0; i < n; i++) {
        if (not mp.count(s[i])) mp[s[i]] = mp.size();
        arr[i] = mp[s[i]];
    }
    m = mp.size();

    vector<int> cnt(m);
    pfxcnt[cnt] = 1;

    for (int i = 0; i < n; i++) {
        int cur = arr[i];
        seen += (cnt[cur] == 0);
        cnt[cur]++;
        if (seen == m) {
            for (int j = 0; j < m; j++) {
                cnt[j]--;
                seen -= (cnt[j] == 0);
            }
        }
        ans += pfxcnt[cnt];
        pfxcnt[cnt]++;
    }

    cout << ans << "\n";

	return 0;
}
