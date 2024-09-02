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

const int N = 1e5, L = 30;

int n, m;
simps arr[N];

bool works(int val, int k) {
    for (int i = 0; i < n; i++) {
        int op = arr[i].first, cur = (arr[i].second & (1 << k) ? 1 : 0);
        if (op == 0) val &= cur;
        else if (op == 1) val |= cur;
        else val ^= cur;
    }
    return val;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string op;
        cin >> op >> arr[i].second;
        if (op == "AND") arr[i].first = 0;
        else if (op == "OR") arr[i].first = 1;
        else arr[i].first = 2;
    }

    int cur = 0, ans = 0;
    for (int i = L - 1; i >= 0; i--) {
        if (works(0, i)) {
            ans |= 1 << i;
            continue;
        }
        if ((cur | (1 << i)) <= m and works(1, i)) {
            ans |= 1 << i;
            cur |= 1 << i;
        }
    }

    cout << ans << "\n";

	return 0;
}
