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

const int N = 2e5 + 1, modval = 1e9 + 7;

int n, arr[N];
ll bit[N];
set<int> vals;
map<int, int> comp;

void setbit(int idx, ll change) {
    for (; idx <= n; idx += idx & (-idx)) bit[idx] = (bit[idx] + change) % modval;
    return;
}

ll getbit(int idx) {
    ll res = 0;
    for (; idx > 0; idx -= idx & (-idx)) res = (res + bit[idx]) % modval;
    return res;
}

int main() {
    memset(bit, 0, sizeof(bit));

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        vals.insert(arr[i]);
    }

    for (int i : vals) comp[i] = comp.size() + 1;

    for (int i = 0; i < n; i++) {
        int cur = comp[arr[i]];
        setbit(cur, getbit(cur - 1) + 1);
    }

    cout << getbit(n) << "\n";

	return 0;
}
