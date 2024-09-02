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

const int K = 1e6, L = 60;
const vector<vector<ll>> Mi = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}, Mn = {{1, 1, 0}, {1, 0, 0}, {0, 0, 1}}, Ms = {{1, 1, 0}, {1, 0, 0}, {-1, 0, 1}};

int k, p, len[K], f[6 * K + 1];
ll n;
bool vis[K];
vector<vector<ll>> fm[L];
map<int, vector<vector<ll>>> seencycm;

vector<vector<ll>> matmul(vector<vector<ll>> a, vector<vector<ll>> b) {
    vector<vector<ll>> res(3, vector<ll>(3));
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) for (int l = 0; l < 3; l++) res[i][j] = (res[i][j] + a[i][l] * b[l][j] + p) % p;
    return res;
}

vector<vector<ll>> matpw(ll num) {
    int cnt = 0;
    vector<vector<ll>> res = Mi;
    while (num) {
        if (num & 1) res = matmul(res, fm[cnt]);
        num >>= 1;
        cnt++;
    }
    return res;
}

int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int u, v, g = exgcd(b, a % b, u, v);
    x = v;
    y = u - a / b * v;
    return g;
}

int inv(int num) {
    if (num == 0) return -1;
    int x, y, g = exgcd(num, k, x, y);
    if (g > 1) return -1;
    return (x % k + k) % k;
}

int nxtcyc(int num) {
    int nxt = inv(num);
    if (nxt == -1) return -1;
    return (ll) num * f[len[nxt] - 1] % k;
}

ll cyclen(int num) {
    int nxt = inv(num);
    if (nxt == -1) return 2e18;
    return len[nxt];
}

int main() {
    clr(len, -1);
    clr(vis, false);

    cin >> n >> k >> p;

    fm[0] = Mn;
    for (int i = 1; i < L; i++) fm[i] = matmul(fm[i - 1], fm[i - 1]);
    
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;
    for (int i = 3; f[i - 2] != 0 or f[i - 1] != 1; i++) {
        f[i] = (f[i - 1] + f[i - 2]) % k;
        if (len[f[i]] == -1) len[f[i]] = i;
    }

    int cycst = f[len[1] - 1];
    while (cycst != -1 and not vis[cycst]) {
        vis[cycst] = true;
        cycst = nxtcyc(cycst);
    }

    ll cycl = 0;
    vector<vector<ll>> cycm = Mi;
    if (cycst != -1) {
        for (int i = cycst; i != cycst or cycm == Mi; i = nxtcyc(i)) {
            cycl += cyclen(i);
            cycm = matmul(matmul(cycm, matpw(cyclen(i) - 1)), Ms);
        }
    }

    vector<vector<ll>> ans = {{1, 0, 1}, {0, 0, 0}, {0, 0, 0}};
    if (n < len[1]) {
        cout << matmul(ans, matpw(n - 1))[0][0] << "\n";
        return 0;
    }

    ans = matmul(matmul(ans, matpw(len[1] - 2)), Ms);;
    n -= len[1];

    int cur = f[len[1] - 1];
    while (true) {
        ll curl = cyclen(cur);
        if (curl > n) {
            cout << matmul(ans, matpw(n))[0][0] << "\n";
            return 0;
        }
        
        if (not seencycm.count(cur)) seencycm[cur] = matmul(matpw(curl - 1), Ms);
        ans = matmul(ans, seencycm[cur]);
        n -= curl;
        cur = nxtcyc(cur);
    }

	return 0;
}
