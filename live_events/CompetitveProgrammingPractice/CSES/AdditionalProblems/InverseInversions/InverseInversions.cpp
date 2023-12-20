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

int n;
ll k, cnt = 0;
vector<int> ans;

int main() {
    cin >> n >> k;
    while (cnt * (cnt + 1) / 2 <= k) cnt++;
    for (int i = 0; i < cnt; i++) ans.push_back(cnt - i);
    k -= cnt * (cnt - 1) / 2;
    for (int i = 0; i < k; i++) ans[i]++;
    ans.push_back(cnt + 1 - k);
    for (int i = cnt + 2; i <= n; i++) ans.push_back(i);

    for (int i : ans) cout << i << " ";
    cout << "\n";

	return 0;
}
