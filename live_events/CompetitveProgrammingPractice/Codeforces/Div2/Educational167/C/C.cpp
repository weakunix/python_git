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

int t;

void subcase() {
    int n, poscnt = 0, negcnt = 0, ans1 = 0, ans2 = 0;
    cin >> n;
    vector<simps> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i].first;
    for (int i = 0; i < n; i++) cin >> arr[i].second;
    for (simps& s : arr) {
        if (s.first == s.second) {
            if (s.first == 1) poscnt++;
            else if (s.first == -1) negcnt++;
            continue;
        }
        if (s.first == 1) {
            ans1++;
            continue;
        }
        if (s.second == 1) {
            ans2++;
            continue;
        }
    }

    while (poscnt > 0) {
        if (ans1 < ans2) ans1++;
        else ans2++;
        poscnt--;
    }

    while (negcnt > 0) {
        if (ans1 < ans2) ans2--;
        else ans1--;
        negcnt--;
    }

    cout << min(ans1, ans2) << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
