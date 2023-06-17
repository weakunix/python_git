#include <iostream>
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
ll ans = 0;
vector<int> pfx = {0};
vector<ll> cnt;

int main() {
    cin >> n;
    cnt.resize(n);
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        pfx.push_back(((pfx.back() + cur) % n + n) % n);
    }
    for (int i : pfx) {
        ans += cnt[i];
        cnt[i]++;
    }
    cout << ans << "\n";
	return 0;
}
