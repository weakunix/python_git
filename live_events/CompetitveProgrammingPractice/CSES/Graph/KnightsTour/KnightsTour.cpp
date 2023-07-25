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

const int dirx[8] = {-2, -2, -1, 1, 2, 2, 1, -1}, diry[8] = {1, -1, -2, -2, -1, 1, 2, 2};

int stx, sty, cnt = 0, visited[8][8], psbl[8][8];

bool cmp(simps a, simps b) {
    return psbl[a.second][a.first] < psbl[b.second][b.first];
}

bool dfs(int x, int y) {
    cnt++;
    visited[y][x] = cnt;
    if (cnt == 64) return true;
    vector<simps> nxt;
    for (int i = 0; i < 8; i++) {
        int newx = x + dirx[i], newy = y + diry[i];
        if (((x >= 0 and x < 8) and (y >= 0 and y < 8)) and visited[newy][newx] == -1) nxt.push_back({newx, newy});
    }
    sort(all(nxt), cmp);
    for (simps s : nxt) {
        if (dfs(s.first, s.second)) return true;
    }
    visited[y][x] = -1;
    cnt--;
    return false;
}

int main() {
    memset(visited, -1, sizeof(visited));
    memset(psbl, 0, sizeof(psbl));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                int x = i + dirx[k], y = j + diry[k];
                psbl[i][j] += ((x >= 0 and x < 8) and (y >= 0 and y < 8));
            }
        }
    }

    cin >> stx >> sty;
    stx--; sty--;
    assert(dfs(stx, sty));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) cout << visited[i][j] << " ";
        cout << "\n";
    }
	return 0;
}
