#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

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
    int n, mn = 0, mx = 1e9, ans;
    vector<int> fail;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, x;
        cin >> a >> x;
        if (a == 1) setmx(mn, x);
        else if (a == 2) setmn(mx, x);
        else fail.push_back(x);
    }
    ans = mx - mn + 1;
    for (int i : fail) if (i >= mn and i <= mx) ans--;
    cout << max(ans, 0) << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
