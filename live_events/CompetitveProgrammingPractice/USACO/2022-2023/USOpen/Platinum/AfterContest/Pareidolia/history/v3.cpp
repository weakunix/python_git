#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5;

int n, q;
string s;
vector<vector<ll>> seg[4 * N];

vector<vector<ll>> bmat = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 1}};

vector<vector<ll>> emat = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, -1, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1}}; //-1 will be changed

vector<vector<ll>> smat = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1}};

vector<vector<ll>> imat = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1}};

vector<vector<ll>> nonemat = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1}};

vector<vector<ll>> operator*(vector<vector<ll>>& a, vector<vector<ll>>& b) {
    vector<vector<ll>> res(8, vector<ll>(8));
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            if (not a[i][k]) continue;
            for (int j = 0; j < 8; j++) res[i][j] += a[i][k] * b[k][j];
        }
    }
    return res;
}

vector<vector<ll>>& getmat(char c, int idx) {
    if (c == 'b') return bmat;
    if (c == 'e') {
        emat[5][6] = n - idx;
        return emat;
    }
    if (c == 's') return smat;
    if (c == 'i') return imat;
    return nonemat;
}

void buildseg(int node, int l, int r) {
    if (l == r) {
        seg[node] = getmat(s[l], l);
        return;
    }
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    seg[node] = seg[2 * node] * seg[2 * node + 1];
    return;
}

void setseg(int node, int l, int r, int idx, char nw) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] = getmat(nw, idx);
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, nw);
    setseg(2 * node + 1, mid + 1, r, idx, nw);
    seg[node] = seg[2 * node] * seg[2 * node + 1];
    return;
}

int main() {
    cin >> s;
    n = s.size();

    buildseg(1, 0, n - 1);
    cout << seg[1][7][6] << "\n";

    cin >> q;
    for (int i = 0; i < q; i++) {
        int idx;
        char nw;
        cin >> idx >> nw;
        idx--;
        s[idx] = nw;
        setseg(1, 0, n - 1, idx, nw);
        cout << seg[1][7][6] << "\n";
    }

	return 0;
}
