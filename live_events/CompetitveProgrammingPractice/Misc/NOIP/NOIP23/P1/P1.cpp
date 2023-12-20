#include <iostream>
#include <cstdio>
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

const int N = 3000;

int n, m;
char mx[N], mn[N];

int main() {
    freopen("dict.in", "r", stdin);
    freopen("dict.out", "w", stdout);

    fill(mx, mx + N, 'a');
    fill(mn, mn + N, 'z');
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            mx[i] = max(c, mx[i]);
            mn[i] = min(c, mn[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        bool works = true;
        for (int j = 0; j < n; j++) {
            if (i != j and mn[i] >= mx[j]) {
                works = false;
                break;
            }
        }
        cout << works;
    }
    cout << "\n";

	return 0;
}
