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

const int N = 2e5;

int n, q, arr[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, cnt;
        cin >> l >> r >> cnt;
        l--; r--;
        for (int j = l; j <= r; j++) {
            if (cnt <= 0) cnt += arr[j];
            else cnt -= arr[j];
        }
        cout << cnt << "\n";
    }

	return 0;
}
