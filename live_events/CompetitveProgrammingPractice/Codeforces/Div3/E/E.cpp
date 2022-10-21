#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void addpf(map<int, int>& pf, int n) {
    while (n % 2 == 0) {
        n /= 2;
        pf[2]++;
    }
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            n /= i;
            pf[i]++;
        }
    }
    if (n > 1) pf[n]++;
    return;
}

simps choose(int a, int b, int c, int d, vector<int>& idx, map<int, int>& pf, int cur, ll prod) {
    if (cur == idx.size()) {
        ll tar = (ll) a * b;
        assert(tar % prod == 0);
        if (c / prod > a / prod and d / (tar / prod) > b / (tar / prod)) return {(c / prod) * prod, (d / (tar / prod)) * (tar / prod)};
        return {-1, -1};
    }
    int val = idx[cur];
    for (int i = 0; i <= pf[val]; i++) {
        simps res = choose(a, b, c, d, idx, pf, cur + 1, prod);
        if (res != make_pair(-1, -1)) return res;
        if (prod * val > c) break;
        prod *= val;
    }
    return {-1, -1};
}

void Subcase() {
    int a, b, c, d;
    vector<int> idx;
    map<int, int> pf;
    cin >> a >> b >> c >> d;
    addpf(pf, a);
    addpf(pf, b);
    for (auto u : pf) idx.push_back(u.first);
    simps ans = choose(a, b, c, d, idx, pf, 0, 1);
    cout << ans.first << " " << ans.second << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
