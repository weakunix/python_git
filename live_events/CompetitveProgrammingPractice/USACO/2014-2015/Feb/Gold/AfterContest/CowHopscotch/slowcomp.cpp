#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

const int modval = 1e9 + 7;
int r, c, k;
vector<int> allbit;
vector<vector<int>> grid, appear, colorbit;

void comp() {
    set<int> unique;
    map<int, int> compmap;
    k = 0;

    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) unique.insert(grid[y][x]);
    }

    for (int i : unique) {
        compmap[i] = k;
        k++;
    }

    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) grid[y][x] = compmap[grid[y][x]];
    }
    
    appear.resize(k);

    return;
}

void getpoints() {
    for (int y = 0; y < r; y++) {
        set<int> row;
        for (int i : grid[y]) row.insert(i);
        for (int i : row) appear[i].push_back(y);
    }
    
    for (int i = 0; i < k; i++) colorbit.push_back(vector<int>(appear[i].size() + 1));

    return;
}

int parentidx(int idx) {
    return idx - (idx & (-idx));
}

int nextidx(int idx) {
    return idx + (idx & (-idx));
}

void setidx(vector<int>& bit, int idx, int addval) {
    while (idx < bit.size()) {
        bit[idx] = (bit[idx] + addval) % modval;
        idx = nextidx(idx);
    }
    return;
}

int getpfx(vector<int>& bit, int idx) {
    int res = 0;
    while (idx > 0) {
        res = (res + bit[idx]) % modval;
        idx = parentidx(idx);
    }
    return res;
}

int main() {
	freopen("hopscotch.in", "r", stdin);
	//freopen("hopscotch.out", "w", stdout);

    cin >> r >> c >> k;
    grid.resize(r, vector<int>(c));
    allbit.resize(r + 1);
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) cin >> grid[y][x];
    }

    comp();
    getpoints();

    for (int x = c - 2; x >= 0; x--) {
        int allcount = 0;
        vector<int> colorcount(k);
        for (int y = r - 1; y >= 0; y--) {
            int color = grid[y][x], idx = appear[color].size() - (lower_bound(all(appear[color]), y) - appear[color].begin()), curres = (((getpfx(allbit, r - y - 1) - allcount) % modval) - ((getpfx(colorbit[color], idx - 1) - colorcount[color]) % modval) + (y < r - 1 and color != grid[r - 1][c - 1])) % modval;
            curres %= modval;
            curres += modval;
            curres %= modval;
            

            if (x == 0 and y == 0) {
                cout << curres << "\n";
                return 0;
            }

            allcount = (allcount + curres) % modval;
            colorcount[color] = (colorcount[color] + curres) % modval;
            setidx(allbit, r - y, curres);
            setidx(colorbit[color], idx, curres);
        }
    }
	
    assert(false);
    return 1;
}
