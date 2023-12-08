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

const int N = 2e5, modval = 998244353;

int t;
ll fac[N];

void subcase() {
    int lead0ans = 0, lead1ans = 0;
    ll ans = 0;
    string s;
    vector<int> lead0, lead1;
    cin >> s;
    
    int cnt = 0;
    char cur = '1';
    for (char c : s) {
        if (c == cur) {
            lead0ans++;
            cnt++;
            continue;
        }
        lead0.push_back(cnt);
        cur = c;
        cnt = 1;
    }
    lead0.push_back(cnt);

    cnt = 0;
    cur = '0';
    for (char c : s) {
        if (c == cur) {
            lead1ans++;
            cnt++;
            continue;
        }
        lead1.push_back(cnt);
        cur = c;
        cnt = 1;
    }
    lead1.push_back(cnt);

    cout << min(lead0ans, lead1ans) << " ";

    if (lead0ans <= lead1ans) {
        ans = fac[lead0ans];
        for (int i : lead0) {
            if (i > 0) ans = ans * i % modval;
        }
    }
    if (lead1ans <= lead0ans) {
        ll cur = fac[lead1ans];
        for (int i : lead1) {
            if (i > 0) cur = cur * i % modval;
        }
        ans = (ans + cur) % modval;
    }
    cout << ans << "\n";

	return;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % modval;

	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
