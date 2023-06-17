#include <iostream>
#include <vector>
#include <deque>
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

int n, m, ans = 0;
deque<int> w;

int main() {
    cin >> n >> m;
    w.resize(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    sort(all(w));
    while (not w.empty()) {
        int cur = w.back();
        w.pop_back();
        if (not w.empty() and w.front() + cur <= m) w.pop_front();
        ans++;
    }
    cout << ans << "\n";
	return 0;
}
