#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
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

const int K = 5e5 + 5;

int k, sz = 1, ans[K], wordidx[K], seen[K], adj[K][26], fail[K], dict[K], par[K], topar[K], ht[K];
string tar;

int gen(int node) {
    if (fail[node] != -1) return fail[node];
    if (par[node] == 0) {
        fail[node] = 0;
        return 0;
    }

    int cur = gen(par[node]);
    while (cur != 0) {
        if (adj[cur][topar[node]] != -1) {
            fail[node] = adj[cur][topar[node]];
            gen(fail[node]);
            if (wordidx[fail[node]] != -1) dict[node] = fail[node];
            else dict[node] = dict[fail[node]];
            return fail[node];
        }

        cur = gen(cur);
    }

    if (adj[0][topar[node]] != -1) {
        fail[node] = adj[0][topar[node]];
        if (wordidx[fail[node]] != -1) dict[node] = fail[node];
    }
    else fail[node] = 0;
    return fail[node];
}

int main() {
    memset(ans, -1, sizeof(ans));
    memset(wordidx, -1, sizeof(wordidx));
    memset(seen, -1, sizeof(seen));
    memset(adj, -1, sizeof(adj));
    memset(fail, -1, sizeof(fail));
    memset(dict, -1, sizeof(dict));
    memset(par, -1, sizeof(par));
    memset(topar, -1, sizeof(topar));
    memset(ht, 0, sizeof(ht));

    fail[0] = 0;

    cin >> tar >> k;
    for (int i = 0; i < k; i++) {
        int node = 0;
        string s;
        cin >> s;
        
        for (int j = 0; j < s.size(); j++) {
            int cur = s[j] - 'a';
            if (adj[node][cur] == -1) {
                adj[node][cur] = sz;
                par[sz] = node;
                topar[sz] = cur;
                ht[sz] = ht[node] + 1;
                sz++;
            }
            node = adj[node][cur];

            if (j == s.size() - 1) {
                if (wordidx[node] == -1) wordidx[node] = i;
                seen[i] = wordidx[node];
            }
        }
    }


    for (int i = 0; i < sz; i++) gen(i);

    int node = 0;
    for (int i = 0; i < tar.size(); i++) {
        int cur = tar[i] - 'a';

        while (node != 0 and adj[node][cur] == -1) node = fail[node];
        if (adj[node][cur] == -1) continue;

        node = adj[node][cur];
        if (wordidx[node] != -1 and ans[wordidx[node]] == -1) ans[wordidx[node]] = i + 2 - ht[node];

        int trav = dict[node];
        while (trav != -1 and ans[wordidx[trav]] == -1) {
            ans[wordidx[trav]] = i + 2 - ht[trav];
            trav = dict[trav];
        }
    }

    for (int i = 0; i < k; i++) cout << ans[seen[i]] << "\n";

	return 0;
}
