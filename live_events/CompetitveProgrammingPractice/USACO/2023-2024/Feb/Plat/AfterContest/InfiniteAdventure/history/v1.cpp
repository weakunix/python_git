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

const int N = 1e5, L = 62;

ll pw2[L];

int n, q, t[N];
vector<int> adj[N], up[N];
vector<ll> upt[N];
vector<vector<int>> nxt[N];
map<ll, int> lg;

int main() {
    pw2[0] = 1;
    lg[1] = 0;
    for (int i = 1; i < L; i++) {
        pw2[i] = pw2[i - 1] * 2;
        lg[pw2[i]] = i;
    }

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        up[i].resize(t[i], -1);
        upt[i].resize(t[i], -1);
        nxt[i].resize(t[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t[i]; j++) {
            int cur;
            cin >> cur;
            cur--;
            adj[i].pb(cur);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t[i]; j++) {
            if (t[adj[i][j]] <= t[i]) { //not going up a layer
                nxt[i][j].pb(adj[i][j]);
                continue;
            }

            //going up a layer
            up[i][j] = adj[i][j];
            upt[i][j] = 1;
        }
    }

    for (int k = 1; k < L; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < t[i]; j++) {
                if (upt[i][j] != -1) continue; //alr going up a layer?

                int node = nxt[i][j][k - 1];
                ll curt = j + (1ll << (k - 1)), remt = 1ll << (k - 1);

                while (remt) {
                    ll modt = curt % t[node], best = (*ub(pw2, pw2 + L, remt)) / 2;
                    
                    if (upt[node][modt] == -1 or upt[node][modt] > best) { //not going up a layer
                        curt += best;
                        remt -= best;
                        node = nxt[node][modt][lg[best]];
                        continue;
                    }

                    if (t[up[node][modt]] <= t[i]) { //go up, but not exceeding original
                        curt += upt[node][modt];
                        remt -= upt[node][modt];
                        node = up[node][modt];
                        continue;
                    }

                    //going up, exceeding original
                    up[i][j] = up[node][modt];
                    upt[i][j] = curt - j + upt[node][modt];
                    node = -1;
                    break;
                }

                if (node != -1) nxt[i][j].pb(node);
            }
        }
    }

    for (int k = 0; k < q; k++) {
        int node;
        ll curt, remt;
        cin >> node >> curt >> remt;
        node--;

        while (remt) {
            ll modt = curt % t[node], best = (*ub(pw2, pw2 + L, remt)) / 2;

            if (upt[node][modt] == -1 or upt[node][modt] > best) { //not going up a layer
                curt += best;
                remt -= best;
                node = nxt[node][modt][lg[best]];
                continue;
            }

            //going up
            curt += upt[node][modt];
            remt -= upt[node][modt];
            node = up[node][modt];
        }

        cout << node + 1 << "\n";
    }

	return 0;
}
