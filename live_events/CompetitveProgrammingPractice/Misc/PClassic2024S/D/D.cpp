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

const int N = 1000;

int t, n, oggrid[N][N], grid[N][N], rowcnt[N][2], colcnt[N][2], cnt;
bool rowvis[N], colvis[N];
threesome ans[N];

void subcase() {
    cnt = 0;
    clr(rowcnt, 0);
    clr(colcnt, 0);
    clr(rowvis, false);
    clr(colvis, false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            oggrid[i][j] = grid[i][j];
            if (grid[i][j] == 1) {
                rowcnt[i][0]++;
                colcnt[j][0]++;
            }
            else if (grid[i][j] == 2) {
                rowcnt[i][1]++;
                colcnt[j][1]++;
            }
            else {
                if (not rowvis[i]) rowvis[i] = true;
                if (not colvis[j]) colvis[j] = true;
            }
        }
    }

    queue<int> rq, cq;
    for (int i = 0; i < n; i++) {
        if (not rowvis[i] and (not rowcnt[i][0] or not rowcnt[i][1])) {
            rq.push(i);
            rowvis[i] = true;
        }
        if (not colvis[i] and (not colcnt[i][0] or not colcnt[i][1])) {
            cq.push(i);
            colvis[i] = true;
        }
    }

    while (rq.size() or cq.size()) {
        if (rq.size()) {
            int cur = rq.front();
            rq.pop();

            if (not rowcnt[cur][0]) ans[cnt] = {0, {cur + 1, 2}};
            else ans[cnt] = {0, {cur + 1, 1}};
            cnt++;

            for (int j = 0; j < n; j++) {
                if (grid[cur][j] == 1) colcnt[j][0]--;
                else if (grid[cur][j] == 2) colcnt[j][1]--;

                if (not colvis[j] and (not colcnt[j][0] or not colcnt[j][1])) {
                    cq.push(j);
                    colvis[j] = true;
                }

                grid[cur][j] = 0;
            }
        }
        else {
            int cur = cq.front();
            cq.pop();

            if (not colcnt[cur][0]) ans[cnt] = {1, {cur + 1, 2}};
            else ans[cnt] = {1, {cur + 1, 1}};
            cnt++;

            for (int j = 0; j < n; j++) {
                if (grid[j][cur] == 1) rowcnt[j][0]--;
                else if (grid[j][cur] == 2) rowcnt[j][1]--;

                if (not rowvis[j] and (not rowcnt[j][0] or not rowcnt[j][1])) {
                    rq.push(j);
                    rowvis[j] = true;
                }

                grid[j][cur] = 0;
            }
        }
    }

    clr(grid, 0);
    for (int i = cnt - 1; i >= 0; i--) {
        if (ans[i].first == 0) for (int j = 0; j < n; j++) grid[ans[i].sec - 1][j] = ans[i].third;
        else for (int j = 0; j < n; j++) grid[j][ans[i].sec - 1] = ans[i].third;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (oggrid[i][j] != grid[i][j]) {
                cout << "-1\n";
                return;
            }
        }
    }

    
    cout << cnt << "\n";
    for (int i = cnt - 1; i >= 0; i--) cout << ans[i].first << " " << ans[i].sec << " " << ans[i].third << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
