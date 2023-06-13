#include <iostream>
#include <string>
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

const int dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};
const char dir[4] = {'R', 'D', 'L', 'U'};

int cnt = 0, ans = 0;
bool visited[9][9];
string s;

void dfs(int x, int y) {
    if (cnt == 48) {
        if (x == 1 and y == 7) ans++;
        return;
    }
    if (x == 1 and y == 7) return;
    cnt++;
    visited[y][x] = true;
    for (int i = 0; i < 4; i++) {
        if (s[cnt - 1] != '?' and s[cnt - 1] != dir[i]) continue;
        int newx = x + dirx[i], newy = y + diry[i], fail = 0;
        if (visited[newy][newx]) continue;
        for (int j = 0; j < 4; j++) fail += visited[newy + diry[j]][newx + dirx[j]];
        if (fail == 2 and visited[newy + diry[i]][newx + dirx[i]]) continue;
        dfs(newx, newy);
    }
    cnt--;
    visited[y][x] = false;
    return;
}

int main() {
    cin >> s;
    for (int i = 0; i < 9; i++) {
        visited[i][0] = true;
        visited[i][8] = true;
        visited[0][i] = true;
        visited[8][i] = true;
    }
    for (int i = 1; i <= 7; i++) {
        for (int j = 1; j <= 7; j++) visited[i][j] = false;
    }
    dfs(1, 1);
    cout << ans << "\n";
	return 0;
}
