#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int N = 2e4, modval = 1234567;

int n, m, par[N];
ll ans = 1;
vector<int> adj[N];
set<int> invalid[N];
map<int, ll> dp[N][5];

void dfs(int node) {
    set<int> psbl[5];

    psbl[0].insert(0);
    for (int i : invalid[node]) psbl[4].insert(i % 10000);

    for (int i : adj[node]) {
        dfs(i);
        
        int curpw = 1;
        for (int j = 2; j < 5; j++) {
            curpw *= 10;
            for (auto& u : dp[i][j]) psbl[j - 1].insert(u.first % curpw);
        }
    }

    int curpw = 1;
    for (int i = 0; i < 4; i++) { //# of parents we care about
        for (int j : psbl[i]) { //seq of parents for i cared parents
            for (int k = 0; k < 10; k++) { //cur digit
                ll cur = 1;
                for (int l : adj[node]) { //child
                    int childseq = j + k * curpw, cnt = i + 1; //what the child sees, how many he cares about
                    while (dp[l][cnt].count(childseq) == 0) {
                        childseq /= 10;
                        cnt--;
                    }
                    cur = cur * dp[l][cnt][childseq] % modval;
                }
                dp[node][i][j] = (dp[node][i][j] + cur) % modval;
            }
        }

        curpw *= 10;
    }

    for (int i : psbl[4]) {
        dp[node][4][i] = 0;
        for (int j = 0; j < 10; j++) {
            if (invalid[node].count(i + j * curpw)) continue;
            ll cur = 1;
            for (int k : adj[node]) {
                int childseq = (i + j * curpw) / 10, cnt = 4;
                while (dp[k][cnt].count(childseq) == 0) {
                    childseq /= 10;
                    cnt--;
                }
                cur = cur * dp[k][cnt][childseq] % modval;
            }
            dp[node][4][i] = (dp[node][4][i] + cur) % modval;
        }
    }

    return;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        adj[par[i]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        invalid[a].insert(b);
    }
    
    dfs(0);

    for (int i = 0; i < n; i++) ans = ans * 10 % modval;
    cout << (ans + modval - dp[0][0][0]) % modval << "\n";

	return 0;
}
