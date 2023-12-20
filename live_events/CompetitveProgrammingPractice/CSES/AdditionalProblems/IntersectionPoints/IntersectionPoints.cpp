#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 2e5 + 2;

int n, bit[N];
ll ans = 0;
set<int> xvals, yvals;
map<int, int> compy;
map<int, vector<int>> adds, rems;
map<int, vector<simps>> queries;

void setbit(int idx, int change) {

    for (; idx < N; idx += idx & (-idx)) {
        bit[idx] += change;
    }
    return;
}

int getbit(int idx) {
    int res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
    return res;
}

int main() {
    memset(bit, 0, sizeof(bit));

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        xvals.insert(x1);
        xvals.insert(x2);
        yvals.insert(y1);
        yvals.insert(y2);

        if (x1 == x2) queries[x1].push_back({y1, y2});
        else {
            adds[x1].push_back(y1);
            rems[x2].push_back(y1);
        }
    }

    for (int i : yvals) compy[i] = compy.size() + 1;
    
    for (int i : xvals) {
        for (int j : rems[i]) setbit(compy[j], -1);
        for (simps s : queries[i]) ans += getbit(compy[s.second] - 1) - getbit(compy[s.first]);
        for (int j : adds[i]) setbit(compy[j], 1);
    }

    cout << ans << "\n";

	return 0;
}
