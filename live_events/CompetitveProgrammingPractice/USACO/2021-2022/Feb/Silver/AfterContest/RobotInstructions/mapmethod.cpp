#include <iostream>
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

int n, tarx, tary;
vector<ll> ans;
vector<simps> instruct;
vector<threesome> firsthalf = {{0, {0, 0}}}, sechalf = {{0, {0, 0}}};
map<simps, vector<ll> > seccount;

int main() {
    cin >> n >> tarx >> tary;
    ans.resize(n);
    instruct.resize(n);
    for (int i = 0; i < n; i++) cin >> instruct[i].first >> instruct[i].second;

    for (int i = 0; i < (n + 1) / 2; i++) {
        int loopcount = firsthalf.size();
        for (int j = 0; j < loopcount; j++) {
            int count = firsthalf[j].first + 1, x = firsthalf[j].sec + instruct[i].first, y = firsthalf[j].third + instruct[i].second;
            firsthalf.push_back({count, {x, y}});
        }
    }

    for (int i = (n + 1) / 2; i < n; i++) {
        int loopcount = sechalf.size();
        for (int j = 0; j < loopcount; j++) {
            int count = sechalf[j].first + 1, x = sechalf[j].sec + instruct[i].first, y = sechalf[j].third + instruct[i].second;
            sechalf.push_back({count, {x, y}});
        }
    }

    for (const threesome& t : sechalf) {
        if (seccount.count(t.second) == 0) seccount[t.second] = vector<ll>(n / 2 + 1);
        seccount[t.second][t.first]++;
    }

    for (const threesome& t : firsthalf) {
        simps complement = {tarx - t.sec, tary - t.third};
        if (seccount.count(complement) == 0) continue;
        
        for (int i = 0; i <= n / 2; i++) ans[t.first + i - 1] += seccount[complement][i];
    }

    for (ll i : ans) cout << i << "\n";

	return 0;
}
