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
const char ord[4] = {'b', 'e', 's', 'i'};
const string tar = "bessie";

int n, q, nxt[N][4];
ll dp[N];
string s;

int toid(char c) {
    if (c == 'b') return 0;
    if (c == 'e') return 1;
    if (c == 's') return 2;
    if (c == 'i') return 3;
    return -1;
}

int getnxt(int idx) {
    for (char c : tar) {
        if (c == 'b' and s[idx] == 'b') continue;
        idx = nxt[idx][toid(c)];
        if (idx == n) return n;
    }
    return idx;
}

ll calc() {
    ll res = 0;

    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 0;
        int idx = getnxt(i);
        if (idx == n) continue;
        dp[i] += n - idx;
        idx = nxt[idx][0];
        if (idx != n) dp[i] += dp[idx];
        res += dp[i];
    }
    
    return res;
}

int main() {
    cin >> s;
    n = s.size();

    fill(nxt[n - 1], nxt[n - 1] + 4, n);
    for (int i = n - 2; i >= 0; i--) for (int j = 0; j < 4; j++) nxt[i][j] = (s[i + 1] == ord[j] ? i + 1 : nxt[i + 1][j]);

    cout << calc() << "\n";

    cin >> q;
    for (int i = 0; i < q; i++) {
        int idx;
        char nw;
        cin >> idx >> nw;
        idx--;
        
        if (toid(s[idx]) != -1) for (int j = idx - 1; j >= 0 and nxt[j][toid(s[idx])] == idx; j--) nxt[j][toid(s[idx])] = nxt[idx][toid(s[idx])];
        if (toid(nw) != -1) for (int j = idx - 1; j >= 0 and nxt[j][toid(nw)] > idx; j--) nxt[j][toid(nw)] = idx;
        s[idx] = nw;

        cout << calc() << "\n";
    }

	return 0;
}
