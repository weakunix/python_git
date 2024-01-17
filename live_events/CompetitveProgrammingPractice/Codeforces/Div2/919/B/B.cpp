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
    int n, k, x, cur = 0, ans;
    vector<int> pos;
    queue<int> neg;

    cin >> n >> k >> x;
    pos.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
        cur += pos[i];
    }
    sort(all(pos));
    for (int i = 0; i < x; i++) {
        neg.push(-pos.back());
        cur -= 2 * pos.back();
        pos.pop_back();
    }
    ans = cur;

    for (int i = 0; i < k; i++) {
        cur -= neg.front();
        neg.pop();
        if (pos.size()) {
            neg.push(-pos.back());
            cur -= 2 * pos.back();
            pos.pop_back();
        }
        setmx(ans, cur);
    }
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
