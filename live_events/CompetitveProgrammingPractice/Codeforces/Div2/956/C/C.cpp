#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5 + 1;

int t, n;
ll tot, vals[3][N];

void subcase() {
    tot = 0;

    cin >> n;
    for (int i = 0; i < 3; i++) for (int j = 1; j <= n; j++) cin >> vals[i][j];
    for (int i = 1; i <= n; i++) tot += vals[0][i];
    tot = (tot + 2) / 3;

    vector<int> ord = {0, 1, 2};
    for (int i = 0; i < 6; i++) {
        next_permutation(all(ord));
        int l = 0, r = n + 1;
        ll sm = 0;
        while (sm < tot) {
            l++;
            sm += vals[ord[0]][l];
        }

        sm = 0;
        while (sm < tot) {
            r--;
            sm += vals[ord[2]][r];
        }

        sm = 0;
        for (int i = l + 1; i < r; i++) sm += vals[ord[1]][i];
        if (sm < tot) continue;

        for (int j = 0; j < 3; j++) {
            if (ord[0] == j) cout << 1 << " " << l << " ";
            else if (ord[1] == j) cout << l + 1 << " " << r - 1 << " ";
            else cout << r << " " << n << " ";
        }
        cout << "\n";
        return;
    }

    cout << "-1\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
