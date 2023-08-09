#include <iostream>
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

int n, q;
vector<vector<int>> pfx;

int main() {
    cin >> n >> q;
    pfx.resize(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            pfx[i][j] = (c == '*') + pfx[i - 1][j] + pfx[i][j - 1] - pfx[i - 1][j - 1];
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << pfx[c][d] - pfx[a - 1][d] - pfx[c][b - 1] + pfx[a - 1][b - 1] << "\n";
    }
	return 0;
}
