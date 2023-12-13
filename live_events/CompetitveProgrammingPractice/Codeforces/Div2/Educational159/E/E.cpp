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

const int N = 1e6 + 1;

int n, totlen = 0, adj[N][26], cnt[N], sz = 1;
ll ans = 0;
string arr[N];

int main() {
    memset(adj, -1, sizeof(adj));
    memset(cnt, 0, sizeof(cnt));

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        totlen += arr[i].size();

        int node = 0;
        for (char c : arr[i]) {
            if (adj[node][c - 'a'] == -1) {
                adj[node][c - 'a'] = sz;
                sz++;
            }
            node = adj[node][c - 'a'];
            cnt[node]++;
        }
    }

    for (int i = 0; i < n; i++) {
        int node = 0;
        reverse(all(arr[i]));
        for (char c : arr[i]) {
            if (adj[node][c - 'a'] == -1) break;
            node = adj[node][c - 'a'];
            ans += cnt[node];
        }
    }

    cout << (ll) 2 * n * totlen - 2 * ans << "\n";

	return 0;
}
