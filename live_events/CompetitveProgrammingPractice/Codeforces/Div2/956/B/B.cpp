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

int t;

void subcase() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m)), tar(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            grid[i][j] = c - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            tar[i][j] = c - '0';
        }
    }

    for (int i = 0; i < n; i++) {
        int a = 0, b = 0;
        for (int j = 0; j < m; j++) {
            a += grid[i][j];
            b += tar[i][j];
        }
        if (a % 3 != b % 3) {
            cout << "NO\n";
            return;
        }
    }

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0;
        for (int j = 0; j < n; j++) {
            a += grid[j][i];
            b += tar[j][i];
        }
        if (a % 3 != b % 3) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
