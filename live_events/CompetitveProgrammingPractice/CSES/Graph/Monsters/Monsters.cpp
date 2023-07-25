#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
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

const int N = 1002, M = 1002, dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};
const char dir[4] = {'R', 'D', 'L', 'U'};

int n, m, distm[N][M], distp[N][M], grid[N][M]; 
simps st;
string ans;
queue<simps> qm, qp, q;

int main() {
    memset(grid, -1, sizeof(grid));
    memset(distm, -1, sizeof(distm));
    memset(distp, -1, sizeof(distp));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c != '#') {
                grid[i][j] = 4;
                distm[i][j] = 1e9;
                distp[i][j] = 1e9;
            }
            if (c == 'M') {
                qm.push({j, i});
                distm[i][j] = 0;
            }
            if (c == 'A') {
                st = {j, i};
                qp.push(st);
                distp[i][j] = 0;
            }
        }
    }
    while (not qm.empty()) {
        int x = qm.front().first, y = qm.front().second;
        qm.pop();
        for (int i = 0; i < 4; i++) {
            int newx = x + dirx[i], newy = y + diry[i];
            if (distm[newy][newx] != 1e9) continue;
            distm[newy][newx] = distm[y][x] + 1;
            qm.push({newx, newy});
        }
    }
    while (not qp.empty()) {
        int x = qp.front().first, y = qp.front().second;
        qp.pop();
        for (int i = 0; i < 4; i++) {
            int newx = x + dirx[i], newy = y + diry[i];
            if (distp[newy][newx] != 1e9) continue;
            distp[newy][newx] = distp[y][x] + 1;
            qp.push({newx, newy});
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) grid[i][j] = (distp[i][j] < distm[i][j]) ? 4 : -1;
    }
    q.push(st);
    while (not q.empty()) {
        int x = q.front().first, y = q.front().second;
        q.pop();
        if ((x == 1 or x == m) or (y == 1 or y == n)) {
            while (x != st.first or y != st.second) {
                int cur = grid[y][x];
                ans += dir[cur];
                x -= dirx[cur];
                y -= diry[cur];
            }
            reverse(all(ans));
            cout << "YES\n" << ans.size() << "\n" << ans << "\n";
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int newx = x + dirx[i], newy = y + diry[i];
            if (grid[newy][newx] != 4) continue;
            grid[newy][newx] = i;
            q.push({newx, newy});
        }
    }
    cout << "NO\n";
	return 0;
}
