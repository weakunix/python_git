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

const int N = 1e5;

__int128 getgcd(__int128 a, __int128 b) {
    while (b % a) {
        b %= a;
        swap(a, b); 
    }   
    return a;
}

struct Frac {
    __int128 num, den;

    Frac() : num(0), den(1) {}

    Frac(__int128 inum, __int128 iden) : num(inum), den(iden) {this->red();}

    ~Frac() {}

    void red() {
        if (not num or not den) {
            num = 0;
            den = 1;
            return;
        }
        __int128 g = getgcd(num, den);
        num /= g;
        den /= g;
        return;
    }
};

Frac operator+(Frac a, Frac b) {
    if (not a.num or not a.den) return b;
    if (not b.num or not b.den) return a;
    __int128 l = a.den / getgcd(a.den, b.den) * b.den;
    return Frac(l / a.den * a.num + l / b.den * b.num, l);
}

Frac operator*(Frac a, Frac b) {
    if ((not a.num or not a.den) or (not b.num or not b.den)) return Frac();
    return Frac(a.num * b.num, a.den * b.den);
}

int n, m;
vector<int> adj[N];
Frac ans[N];

void dfs(int node, Frac cur) {
    if (adj[node].empty()) {
        ans[node] = ans[node] + cur;
        return;
    }
    cur = cur * Frac(1, adj[node].size());
    for (int i : adj[node]) dfs(i, cur);
    return;
}

string printans(__int128 num) {
    string res;
    while (num) {
        res += '0' + (num % 10);
        num /= 10;
    }
    reverse(all(res));
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int cnt;
        cin >> cnt;
        adj[i].resize(cnt);
        for (int j = 0; j < cnt; j++) {
            cin >> adj[i][j];
            adj[i][j]--;
        }
    }

    for (int i = 0; i < m; i++) dfs(i, Frac(1, 1));

    for (int i = 0; i < n; i++) if (adj[i].empty()) cout << printans(ans[i].num) << " " << printans(ans[i].den) << "\n";

	return 0;
}
