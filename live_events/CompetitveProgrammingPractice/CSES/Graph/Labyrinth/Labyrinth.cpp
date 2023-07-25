#include <iostream>
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

int n, m, visited[N][M];
simps st, en;
string ans;
queue<simps> q;

int main() {
    memset(visited, -1, sizeof(visited));

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c != '#' and c != 'A') visited[i][j] = 4;
            if (c == 'A') st = {j, i};
            else if (c == 'B') en = {j, i};
        }
    }
    q.push(st);
    while (not q.empty()) {
        simps loc = q.front();
        q.pop();
        if (loc == en) {
            while (loc != st) {
                int cur = visited[loc.second][loc.first];
                ans += dir[cur];
                loc = {loc.first - dirx[cur], loc.second - diry[cur]};
            }
            reverse(all(ans));
            cout << "YES\n" << ans.size() << "\n" << ans << "\n";
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            int newx = loc.first + dirx[i], newy = loc.second + diry[i];
            if (visited[newy][newx] != 4) continue;
            visited[newy][newx] = i;
            q.push({newx, newy});
        }
    }
    cout << "NO\n";
	return 0;
}
