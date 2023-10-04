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

int k, sz = 1, seen[K], wordidx[K], adj[K][26], fail[K], dict[K], ans[K], par[K], topar[K];
string tar;

int gen(int node) {
    if (fail[node] != -1) return fail[node];
    if (par[node] == 0) {
        fail[node] = 0;
        return 0;
    }

    int cur = par[node];
    if (fail[cur] == -1) gen(cur);
    cur = fail[cur];
    while (cur != 0) {
        if (adj[cur][topar[node]] != -1) {
            fail[node] = adj[cur][topar[node]];
            if (fail[fail[node]] == -1) gen(fail[node]);
            if (wordidx[fail[node]] == -1) dict[node] = dict[fail[node]];
            else dict[node] = fail[node];
            return fail[node];
        }
        
        if (fail[cur] == -1) gen(cur);
        cur = fail[cur];
    }
    if (adj[0][topar[node]] != -1) {
        fail[node] = adj[0][topar[node]];
        if (wordidx[fail[node]] != -1) dict[node] = fail[node];
    }
    else fail[node] = 0;
    return fail[node];
}

int main() {
    memset(seen, -1, sizeof(seen));
    memset(wordidx, -1, sizeof(wordidx));
    memset(adj, -1, sizeof(adj));
    memset(fail, -1, sizeof(fail));
    memset(dict, -1, sizeof(dict));
    memset(ans, 0, sizeof(ans));
    memset(par, -1, sizeof(par));
    memset(topar, -1, sizeof(topar));

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
                sz++;
            }
            node = adj[node][cur];
            if (j == s.size() - 1) {
                if (wordidx[node] == -1) wordidx[node] = i;
                else seen[i] = wordidx[node];
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
        if (wordidx[node] != -1) ans[wordidx[node]]++;

        int trav = dict[node];
        while (trav != -1) {
            ans[wordidx[trav]]++;
            trav = dict[trav];
        }
    }

    for (int i = 0; i < k; i++) cout << (seen[i] == -1 ? ans[i] : ans[seen[i]]) << "\n";
	return 0;
}
