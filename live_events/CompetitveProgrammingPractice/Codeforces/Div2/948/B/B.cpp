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
    int x;
    vector<int> ans(32);
    cin >> x;
    for (int i = 0; i < 32; i++) if ((1 << i) & x) ans[i] = 1;
    for (int j = 0; j < 32; j++) {
        for (int i = 30; i >= 0; i--) {
            if (ans[i] and ans[i + 1]) {
                if (ans[i + 1] == 1 and ans[i] == 1) {
                    ans[i + 2]++;
                    ans[i + 1] = 0;
                    ans[i] = -1;
                }
                else if (ans[i + 1] == -1 and ans[i] == -1) {
                    ans[i + 2]--;
                    ans[i + 1] = 0;
                    ans[i] = 1;
                }
                else if (ans[i + 1] == 1 and ans[i] == -1) {
                    ans[i + 1] = 0;
                    ans[i] = 1;
                }
                else {
                    ans[i + 1] = 0;
                    ans[i] = -1;
                }
            }
        }
    }
    cout << 32 << "\n";
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
