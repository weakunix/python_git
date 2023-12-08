#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
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

struct TrieNode {
    int ht;
    bool isword;
    vector<simps> currng;
    map<char, TrieNode*> adj;

    TrieNode(int setht) {
        ht = setht;
        isword = false;
        return;
    }
};

const int N = 100, M = 1e6 + 1;

int n, m, dp[M];
string s, words[N];
map<int, vector<int>> sortedrng;
map<char, vector<int>> locs;
map<simps, int> rng;
TrieNode* rt = new TrieNode(0);

void dfs(TrieNode* node, TrieNode* par, char prvc) {
    if (node->ht == 1) {
        for (int i : locs[prvc]) node->currng.push_back({i, i});
    }
    else if (node->ht > 1) {
        for (simps& p : par->currng) {
            auto it = upper_bound(all(locs[prvc]), p.second);
            if (it == locs[prvc].end()) break;
            while (node->currng.size() and node->currng.back().second == *it) node->currng.pop_back();
            if (*it - p.first + 1 <= 1000) node->currng.push_back({p.first, *it});
        }
    }

    if (node->isword) {
        for (simps& p : node->currng) {
            sortedrng[p.second].push_back(p.first);
            rng[p] = max({node->ht, rng[p]});
        }
    }

    for (auto& u : node->adj) dfs(u.second, node, u.first);

    return;
}

int main() {
    memset(dp, 0, sizeof(dp));

    cin >> n;
    for (int i = 0; i < n; i++) cin >> words[i];
    cin >> s;
    m = s.size();

    for (int i = 0; i < m; i++) locs[s[i]].push_back(i);
    
    for (int i = 0; i < n; i++) {
        string& w = words[i];
        TrieNode* cur = rt;
        for (char c : w) {
            if (not cur->adj.count(c)) {
                TrieNode* nwnode = new TrieNode(cur->ht + 1);
                cur->adj[c] = nwnode;
            }
            cur = cur->adj[c];
        }
        cur->isword = true;
    }

    dfs(rt, nullptr, '0');

    for (int i = 1; i <= m; i++) {
        dp[i] = dp[i - 1];
        for (int j : sortedrng[i - 1]) dp[i] = max(rng[make_pair(j, i - 1)] + dp[j], dp[i]);
    }

    cout << dp[m] << "\n";

	return 0;
}
