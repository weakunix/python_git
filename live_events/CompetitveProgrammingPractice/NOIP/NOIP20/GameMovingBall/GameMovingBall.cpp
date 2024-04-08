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

const int N = 52;

int n, m;
vector<int> stck[N];
vector<simps> ans;

void mv(int a, int b) {
    ans.pb({a, b});
    stck[b].pb(stck[a].back());
    stck[a].bp();
    return;
}

void solve(int l, int r) {
    if (l == r) return;

    int mid = l + (r - l) / 2;
    
    int a = l, b = r;
    while (a < b) {
        int k = 0;

        for (int i = 0; i < m; i++) k += (stck[a][i] > mid);

        for (int i = 0; i < k; i++) mv(b, n + 1);

        for (int i = 0; i < m; i++) {
            if (stck[a].back() <= mid) mv(a, n + 1);
            else mv(a, b);
        }

        for (int i = 0; i < m - k; i++) mv(n + 1, a);
        for (int i = 0; i < k; i++) mv(b, a);

        for (int i = 0; i < m - k; i++) mv(b, n + 1);

        for (int i = 0; i < k; i++) mv(a, b);

        for (int i = 0; i < m; i++) {
            int cur = stck[n + 1].back();
            if (cur <= mid) {
                if (stck[a].size() < m) mv(n + 1, a);
                else mv(n + 1, b);
            }
            else {
                if (stck[b].size() < m) mv(n + 1, b);
                else mv(n + 1, a);
            }
        }
        
        bool works = true;
        for (int i = 0; i < m; i++) {
            if (stck[a][i] > mid) {
                works = false;
                break;
            }
        }
        if (works) a++;

        works = true;
        for (int i = 0; i < m; i++) {
            if (stck[b][i] <= mid) {
                works = false;
                break;
            }
        }
        if (works) b--;
    }

    solve(l, mid);
    solve(mid + 1, r);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        stck[i].resize(m);
        for (int j = 0; j < m; j++) cin >> stck[i][j];
    }

    solve(1, n);
    
    cout << ans.size() << "\n";
    for (simps s : ans) cout << s.first << " " << s.second << "\n";

	return 0;
}
