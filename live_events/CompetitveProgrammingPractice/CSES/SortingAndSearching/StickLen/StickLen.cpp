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

int n, l = 1, r = 1e9;
vector<int> len;

ll getcost(int tar) {
    ll res = 0;
    for (int i : len) res += abs(tar - i);
    return res;
}

int main() {
    cin >> n;
    len.resize(n);
    for (int i = 0; i < n; i++) cin >> len[i];
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (getcost(mid) <= getcost(mid - 1)) l = mid;
        else r = mid - 1;
    }
    assert(l == r);
    cout << getcost(l) << "\n";
	return 0;
}
