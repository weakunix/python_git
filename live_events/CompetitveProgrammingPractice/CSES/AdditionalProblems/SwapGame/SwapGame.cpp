#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
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
 
const int dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};
const vector<vector<int>> tar = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
 
vector<bool> vis(387420489);
vector<vector<int>> oggrid(3, vector<int>(3));
 
vector<vector<int>> togrid(int hsh) {
    vector<vector<int>> res(3, vector<int>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res[i][j] = hsh % 9;
            hsh /= 9;
        }
    }
    return res;
}
 
int tohsh(const vector<vector<int>>& grid) {
    int res = 0, curpw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            res += curpw * grid[i][j];
            curpw *= 9;
        }
    }
    return res;
}
 
int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> oggrid[i][j];
            oggrid[i][j]--;
        }
    }
 
    queue<simps> q;
    q.push({tohsh(oggrid), 0});
    vis[tohsh(oggrid)] = true;
 
    while (not q.empty()) {
        int curh = q.front().first, dist = q.front().second;
        vector<vector<int>> curg = togrid(curh);
        q.pop();
 
        if (curh == tohsh(tar)) {
            cout << dist << "\n";
            return 0;
        }
 
        for (int i = 0; i < 4; i++) {
            int x1 = 1 + dirx[i], y1 = 1 + diry[i];
            for (int j = 0; j < 4; j++) {
                if (j == i) continue;
                int x2 = x1 + dirx[j], y2 = y1 + diry[j];
                swap(curg[y1][x1], curg[y2][x2]);
                int nwh = tohsh(curg);
                if (not vis[nwh]) {
                    vis[nwh] = true;
                    q.push({nwh, dist + 1});
                }
                swap(curg[y1][x1], curg[y2][x2]);
            }
        }
    }
 
    assert(false);
 
	return 0;
}
