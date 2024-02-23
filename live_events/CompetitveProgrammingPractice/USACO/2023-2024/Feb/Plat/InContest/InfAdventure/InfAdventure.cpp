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

const int N = 1e5;

int n, q, t[N];
vector<int> c[N];

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) {
        c[i].resize(t[i]);
        for (int j = 0; j < t[i]; j++) {
            cin >> c[i][j];
            c[i][j]--;
        }
    }
    for (int i = 0; i < q; i++) {
        int v;
        ll tm, d;
        cin >> v >> tm >> d;
        v--;
        tm %= 1 << 18;
        for (int j = 0; j < d; j++) {
            v = c[v][tm % t[v]];
            tm++;
        }
        cout << v + 1 << "\n";
    }
	return 0;
}
