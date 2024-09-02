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

struct Trie {
    map<char, Trie*> nxt;

    Trie() {}

    ~Trie() {}
};

int ans = 1;
Trie* rt;

int main() {
    rt = new Trie();
    string s;
    while (getline(cin, s)) {
        Trie* cur = rt;
        for (char c : s) {
            if (not cur->nxt.count(c)) {
                ans++;
                cur->nxt[c] = new Trie();
            }
            cur = cur->nxt[c];
        }
    }
    cout << ans << "\n";
	return 0;
}
