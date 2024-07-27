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
typedef unsigned long long ull;
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

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}


const int N = 4e5;

int n, m, s[N][16], ans = 0;
ull a1, a2;
bool raw[N][256];
vector<int> mp[16][1 << 16];

void gen() {
    for (int i = 0; i < n; i++) for (int j = 0; j < 256; j++) raw[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}

int gethex(char c) {
    if (c >= '0' and c <= '9') return c - '0';
    return 10 + (c - 'A');
}

int main() {
    cin >> n >> m >> a1 >> a2;
    
    gen();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 16; j++) {
            s[i][j] = 0;
            for (int k = 0; k < 16; k++) {
                s[i][j] = 2 * s[i][j] + raw[i][16 * j + k];
            }
            mp[j][s[i][j]].pb(i);
        }
    }

    for (int i = 0; i < m; i++) {
        int cur[16], dif;
        string curhex;
        vector<int> psbl;
        cin >> curhex >> dif;

        for (int j = 0; j < 16; j++) {
            cur[j] = 0;
            for (int k = 0; k < 4; k++) cur[j] = 16 * cur[j] + (gethex(curhex[4 * j + k]) ^ (ans ? 15 : 0));
            for (int k : mp[j][cur[j]]) psbl.pb(k);
        }
        
        ans = 0;
        for (int j : psbl) {
            int cnt = 0;
            for (int k = 0; k < 16; k++) cnt += __builtin_popcount(cur[k] ^ s[j][k]);
            if (cnt <= dif) {
                ans = 1;
                break;
            }
        }

        cout << ans << "\n";
    }

	return 0;
}
