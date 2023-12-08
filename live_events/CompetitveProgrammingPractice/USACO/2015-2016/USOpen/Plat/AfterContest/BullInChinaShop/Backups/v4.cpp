//==================================================SET UP==================================================//
#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

//==================================================CONSTS==================================================//

const int K = 100, N = 500, M = 500, modval = 1e9 + 7, hshcnt = 2; //CHANGE HSHCNT IF NEEDED
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> hshdist(100, modval - 1); //CHANGE L AND R IF NEEDED
const ll B[hshcnt] = {hshdist(rng), hshdist(rng)};
ll pw[hshcnt][N * M], invpw[hshcnt][N * M];

//==================================================PRE-CALC==================================================//

ll fastpw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        a = a * a % modval;
        b >>= 1;
    }
    return res;
}

//==================================================STRUCTS==================================================//

struct Hsh {
    vector<ll> hsh;

    Hsh() {
        hsh.resize(hshcnt);
        return;
    }

    void shift(int num) {
        for (int i = 0; i < hshcnt; i++) {
            if (num >= 0) hsh[i] = hsh[i] * pw[i][num] % modval;
            else hsh[i] = hsh[i] * invpw[i][-num] % modval;
        }
        return;
    }

    Hsh shifted(int num) {
        Hsh res = *this;
        res.shift(num);
        return res;
    }

    void upd(int val, int pos) {
        for (int i = 0; i < hshcnt; i++) hsh[i] = (hsh[i] + val * pw[i][pos] % modval) % modval;
        return;
    }
};

Hsh operator-(Hsh a, Hsh b) {
    Hsh res;
    for (int i = 0; i < hshcnt; i++) res.hsh[i] = (a.hsh[i] - b.hsh[i] + modval) % modval;
    return res;
}

bool operator<(const Hsh& a, const Hsh& b) {
    return a.hsh < b.hsh;
}


//==================================================VARS==================================================//

int k, n, m, r[K][8], c[K][8], ogtl, tl[K][8], ogpfx[N * M], curpfx[N * M], ogtopcnt[N], alltopcnt[K][8][N];
bool works[K];
deque<deque<int>> oggrid, allgrids[K];
Hsh oghsh, allhsh[K][8];
set<threesome> ans;
map<Hsh, vector<int>> cnt;

//==================================================DEBUG==================================================//

void printgrid(deque<deque<int>>& grid) {
    cout << "\n";
    for (deque<int>& d : grid) {
        for (int i : d) cout << i << " ";
        cout << "\n";
    }
    return;
}

//==================================================ANSWER COMPUTATION==================================================//

int fromtop(int idx1, int ori1, int idx2, int ori2, int offset) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (ogtopcnt[mid] > alltopcnt[idx1][ori1][mid] + (mid - offset < 0 ? 0 : alltopcnt[idx2][ori2][mid - offset])) r = mid;
        else l = mid + 1;
    }
    assert(l == r);
    return l;
}

void calc(int idx, int ori) {
    int curtl = ogtl - tl[idx][ori];
    if (curtl < 0) return;

    Hsh tar = oghsh - allhsh[idx][ori].shifted(curtl);

    int l = 0, r = n * m - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (ogpfx[mid] - (mid - curtl >= 0 ? curpfx[mid - curtl] : 0) >= 1) r = mid;
        else l = mid + 1;
    }
    assert(l == r);
    int x = l % m, y = l / m;

    for (int i = 0; i < k; i++) {
        if (i == idx or not works[i]) continue;

        for (int o = 0; o < 8; o++) {
            curtl = x - tl[i][o];
            if (curtl < 0) continue;
            
            Hsh curtar = tar - allhsh[i][o].shifted(y * m + curtl);
            curtar.shift(-m * fromtop(idx, ori, i, o, y));

            if (cnt.count(curtar) > 0) {
                for (int p : cnt[curtar]) {
                    if (p != idx and p != i) {
                        int a = p, b = i, c = idx;
                        if (c < b) swap(b, c);
                        if (c < a) swap(a, c);
                        if (b < a) swap(a, b);
                        ans.insert({a, {b, c}});
                    }
                }
            }
        }
    }
    return;
}

//==================================================PIECE INFORMATION==================================================//

int gettl(deque<deque<int>>& grid) { //get tl
    for (int i = 0; i < grid[0].size(); i++) if (grid[0][i] != 0) return i;
    assert(false);
    return -1;
}

void setpfx(deque<deque<int>>& grid, int (&pfx)[N * M]) {
    int r = grid.size(), c = grid[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) pfx[i * m + j] = (i == 0 and j == 0 ? 0 : pfx[i * m + j - 1]) + (i < r and j < c ? (grid[i][j] > 0) : 0);
    }

    return;
}

void settopcnt(deque<deque<int>>& grid, int (&topcnt)[N]) {
    int r = grid.size(), c = grid[0].size();
    for (int i = 0; i < n; i++) {
        topcnt[i] = i == 0 ? 0 : topcnt[i - 1];
        if (i >= r) continue;
        for (int j = 0; j < c; j++) topcnt[i] += (grid[i][j] > 0);
    }
    return;
}

Hsh gethsh(deque<deque<int>>& grid) {
    int r = grid.size(), c = grid[0].size();
    Hsh res;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) res.upd(grid[i][j], i * m + j);
    }
    return res;
}

void cntadd(Hsh& curhsh, int elem) {
    vector<int>& cur = cnt[curhsh];
    if (cur.size() and cur.back() == elem) return;
    cur.push_back(elem);
    return;
}

void setpieceinfo(deque<deque<int>>& grid, int idx, int ori) {
    r[idx][ori] = grid.size();
    c[idx][ori] = grid[0].size();
    tl[idx][ori] = gettl(grid);
    settopcnt(grid, alltopcnt[idx][ori]);

    Hsh cur = gethsh(grid);
    allhsh[idx][ori] = cur;

    cntadd(cur, idx);
    for (int i = 0; i + c[idx][ori] < m; i++) {
        cur.shift(1);
        cntadd(cur, idx);
    }
    return;
}

//==================================================PIECE PROCESSING==================================================//

void rotgrid(deque<deque<int>>& grid) { //rotate 90 deg cc
    deque<deque<int>> nw;
    for (int i = grid[0].size() - 1; i >= 0; i--) {
        nw.push_back({});
        for (int j = 0; j < grid.size(); j++) nw.back().push_back(grid[j][i]);
    }
    swap(nw, grid);
    return;
}

void reflgrid(deque<deque<int>>& grid) { //reflect over x axis
    for (int i = 0; i < grid.size() / 2; i++) swap(grid[i], grid[grid.size() - i - 1]);
    return;
}

void setpiece(int idx) { //take in piece, scrap sides
    int curr, curc;
    cin >> curr >> curc;

    deque<deque<int>>& grid = idx == -1 ? oggrid : allgrids[idx];
    grid.resize(curr, deque<int>(curc));
    for (int i = 0; i < curr; i++) {
        for (int j = 0; j < curc; j++) {
            char cur;
            cin >> cur;
            grid[i][j] = cur == '.' ? 0 : (cur - 'a') + 1;
        }
    }

    while (true) { //scrap top
        bool rem = true;
        for (int i : grid[0]) {
            if (i != 0) {
                rem = false;
                break;
            }
        }
        if (not rem) break;
        grid.pop_front();
        curr--;
    }

    while (true) { //scrap bottom
        bool rem = true;
        for (int i : grid.back()) {
            if (i != 0) {
                rem = false;
                break;
            }
        }
        if (not rem) break;
        grid.pop_back();
        curr--;
    }

    while (true) { //scrap left
        bool rem = true;
        for (deque<int>& d : grid) {
            if (d[0] != 0) {
                rem = false;
                break;
            }
        }
        if (not rem) break;
        for (deque<int>& d : grid) d.pop_front();
        curc--;
    }

    while (true) { //scrap right
        bool rem = true;
        for (deque<int>& d : grid) {
            if (d.back() != 0) {
                rem = false;
                break;
            }
        }
        if (not rem) break;
        for (deque<int>& d : grid) d.pop_back();
        curc--;
    }

    if (idx == -1) { //take in original piece
        n = curr;
        m = curc;
        ogtl = gettl(grid);
        setpfx(grid, ogpfx);
        settopcnt(grid, ogtopcnt);
        oghsh = gethsh(grid);
        return;
    }

    if (curr > n or curc > m) return;
    works[idx] = true;

    for (int i = 0; i < 4; i++) {
        setpieceinfo(grid, idx, i);
        rotgrid(grid);
    }
    reflgrid(grid);
    for (int i = 4; i < 8; i++) {
        setpieceinfo(grid, idx, i);
        rotgrid(grid);
    }
    reflgrid(grid);

    return;
}

//==================================================MAIN==================================================//

int main() {
    for (int i = 0; i < hshcnt; i++) {
        pw[i][0] = 1;
        invpw[i][0] = 1;
        invpw[i][1] = fastpw(B[i], modval - 2);
        for (int j = 1; j < N * M; j++) pw[i][j] = pw[i][j - 1] * B[i] % modval;
        for (int j = 2; j < N * M; j++) invpw[i][j] = invpw[i][j - 1] * invpw[i][1] % modval;
    }

    cin >> k;
    setpiece(-1);
    for (int i = 0; i < k; i++) setpiece(i);

    for (int i = 0; i < k; i++) {
        if (not works[i]) continue;
        for (int j = 0; j < 4; j++) {
            setpfx(allgrids[i], curpfx);
            calc(i, j);
            rotgrid(allgrids[i]);
        }
        reflgrid(allgrids[i]);
        for (int j = 4; j < 8; j++) {
            setpfx(allgrids[i], curpfx);
            calc(i, j);
            rotgrid(allgrids[i]);
        }
    }

    cout << ans.size() << "\n";
	return 0;
}
