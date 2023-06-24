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

ll a, b, ans = 0;
vector<ll> pow9(19), pow10(19);

vector<int> getdig(ll num) {
    vector<int> res;
    while (num > 0) {
        res.push_back(num % 10);
        num /= 10;
    }
    return res;
}

ll solve(vector<int> diga, vector<int> digb, int prvdig) {
    assert(diga.size() == digb.size());
    if (diga.empty()) return 1;
    if (diga.back() == digb.back()) {
        if (prvdig == diga.back()) return 0;
        prvdig = diga.back();
        diga.pop_back();
        digb.pop_back();
        return solve(diga, digb, prvdig);
    }
    ll res = (digb.back() - diga.back() - 1 - (prvdig > diga.back() and prvdig < digb.back())) * pow9[diga.size() - 1];
    if (diga.back() != prvdig) {
        int curdig = diga.back();
        vector<int> newdigb(diga.size() - 1, 9);
        diga.pop_back();
        res += solve(diga, newdigb, curdig);
    }
    if (digb.back() != prvdig) {
        int curdig = digb.back();
        vector<int> newdiga(digb.size() - 1, 0);
        digb.pop_back();
        res += solve(newdiga, digb, curdig);
    }
    return res;
}

int main() {
    pow9[0] = 1;
    pow10[0] = 1;
    for (int i = 1; i < 19; i++) {
        pow9[i] = 9 * pow9[i - 1];
        pow10[i] = 10 * pow10[i - 1];
    }
    cin >> a >> b;
    if (a == 0) {
        ans = 1;
        a = 1;
    }
    if (b == 1e18) b--;
    while (a <= b) {
        ll curb = min(*upper_bound(all(pow10), a) - 1, b);
        vector<int> diga = getdig(a), digb = getdig(curb);
        ans += solve(diga, digb, -1);
        a = curb + 1;
    }
    cout << ans << "\n";
	return 0;
}
