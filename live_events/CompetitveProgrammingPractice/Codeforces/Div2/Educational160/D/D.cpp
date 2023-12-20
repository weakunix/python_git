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

const int N = 3e5 + 1, modval = 998244353;

int t;
ll pw[N];

void subcase() {
    int n;
    ll ans = 1;
    vector<vector<int>> seq;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (seq.empty() or seq.back().back() > cur) seq.push_back({cur});
        else seq.back().push_back(cur);
    }

    for (int i = 0; i < seq.size() - 1; i++) {
        int nxt = seq[i + 1][0];
        ll cur = pw[seq[i].size() - 1];
        if (nxt > seq[i][0]) cur = (cur + pw[seq[i].size() - (lower_bound(all(seq[i]), nxt) - seq[i].begin()) - 1]) % modval;
        else cur = (cur + 1) % modval;
        ans = ans * cur % modval;
    }

    ans = ans * pw[seq.back().size() - 1] % modval;
    cout << ans << "\n";

	return;
}

int main() {
   	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = 2 * pw[i - 1] % modval;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
