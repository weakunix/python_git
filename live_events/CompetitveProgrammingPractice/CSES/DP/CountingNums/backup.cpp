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
ll a, b, ans = 0;
vector<int> diga, digb;
vector<ll> pow9 = {1};

void solve(ll l, ll r) {
    
    return;
}

int main() {
    cin >> a >> b;
    while (a > 0 or b > 0) {
        diga.push_back(a % 10);
        digb.push_back(b % 10);
        a /= 10;
        b /= 10;
    }
    n = diga.size();
    for (int i = 0; i < n; i++) pow9.push_back(pow9.back() * 9);
    solve(a, b);
    cout << ans << "\n";
	return 0;
}
