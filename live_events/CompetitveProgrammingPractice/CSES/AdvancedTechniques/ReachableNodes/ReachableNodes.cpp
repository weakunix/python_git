#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <utility>
#include <queue>
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

const int N = 5e4;

int n, m, outdeg[N];
vector<int> revadj[N];
queue<int> ord;
bitset<N> ans[N];

int main() {
    memset(outdeg, 0, sizeof(outdeg));

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        revadj[b].push_back(a);
        outdeg[a]++;
    }

    for (int i = 0; i < n; i++) {
        ans[i].set(i);
        if (not outdeg[i]) ord.push(i);
    }

    while (ord.size()) {
        int node = ord.front();
        ord.pop();
        for (int i : revadj[node]) {
            outdeg[i]--;
            ans[i] |= ans[node];
            if (not outdeg[i]) ord.push(i);
        }
    }

    for (int i = 0; i < n; i++) cout << ans[i].count() << "\n";

	return 0;
}
