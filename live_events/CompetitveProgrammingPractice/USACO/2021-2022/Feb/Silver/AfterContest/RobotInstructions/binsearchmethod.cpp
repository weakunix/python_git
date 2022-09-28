#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<simps, int> threesome;

#define all(v) v.begin(), v.end()

int n, tarx, tary;
vector<ll> ans;
vector<simps> instruct;
vector<threesome> firsthalf = {{{0, 0}, 0}}, sechalf = {{{0, 0}, 0}};

int main() {
    cin >> n >> tarx >> tary;
    ans.resize(n);
    instruct.resize(n);
    for (int i = 0; i < n; i++) cin >> instruct[i].first >> instruct[i].second;

    for (int i = 0; i < (n + 1) / 2; i++) {
        int loopcount = firsthalf.size();
        for (int j = 0; j < loopcount; j++) {
            int count = firsthalf[j].second + 1;
            ll x = firsthalf[j].first.first + instruct[i].first, y = firsthalf[j].first.second + instruct[i].second;
            firsthalf.push_back({{x, y}, count});
        }
    }

    for (int i = (n + 1) / 2; i < n; i++) {
        int loopcount = sechalf.size();
        for (int j = 0; j < loopcount; j++) {
            int count = sechalf[j].second + 1;
            ll x = sechalf[j].first.first + instruct[i].first, y = sechalf[j].first.second + instruct[i].second;
            sechalf.push_back({{x, y}, count});
        }
    }

    sort(all(sechalf));

    for (const threesome& t : firsthalf) {
        threesome complement = {{tarx - t.first.first, tary - t.first.second}, 0};
        auto it = lower_bound(all(sechalf), complement);
        while (it != sechalf.end() and it->first == complement.first) {
            ans[t.second + it->second - 1]++;
            it++;
        }
    }

    for (ll i : ans) cout << i << "\n";

	return 0;
}
