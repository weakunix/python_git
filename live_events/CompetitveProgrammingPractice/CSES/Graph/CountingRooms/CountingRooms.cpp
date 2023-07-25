#include <iostream>
#include <cstring>
#include <vector>
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

int n, m, ans = 0;
bool visited[N][M];

void dfs(int y, int x) {
    visited[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int newx = x + dirx[i], newy = y + diry[i];
        if (not visited[newy][newx]) dfs(newy, newx);
    }
    return;
}

int main() {
    memset(visited, true, sizeof(visited));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            visited[i][j] = (c == '#');
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (visited[i][j]) continue;
            ans++;
            dfs(i, j);
        }
    }
    cout << ans << "\n";
	return 0;
}
