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

const int N = 1e5 + 1;
int lg[N];

int n, cnt[2];
ll ans = 0;

int main() {
    lg[1] = 0;
    for (int i = 2; i < N; i++) lg[i] = lg[i / 2] + 1;

    cin >> n;
    for (int i = 0; i < n; i++) {
        bool cur;
        cin >> cur;
        cnt[cur]++;
    }

    for (int i = 0; i < 2; i++) {
        if (not cnt[i]) continue;

        int cur = cnt[i], l = lg[cur], k = 2 * (cur - (1 << l));
        ans += (l + 1) * k + l * (cur - k);
    }

    cout << ans << "\n";

	return 0;
}
