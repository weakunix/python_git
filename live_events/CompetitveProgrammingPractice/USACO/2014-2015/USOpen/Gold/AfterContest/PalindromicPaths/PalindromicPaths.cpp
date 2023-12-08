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

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 500, modval = 1e9 + 7, topx[4] = {-1, 0, -1, 0}, topy[4] = {0, -1, 0, -1}, botx[4] = {1, 1, 0, 0}, boty[4] = {0, 0, 1, 1};

int n;
string arr[N];
vector<vector<ll>> prv;

int main() {
    cin >> n;
    prv.resize(n, vector<ll>(n));
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) prv[i][j] = i == j;
    }

    for (int i = 0; i < n - 1; i++) {
        vector<vector<ll>> cur(n, vector<ll>(n));
        for (int j = 0; j < n - i; j++) {
            for (int k = i; k < n; k++) {
                for (int d = 0; d < 4; d++) {
                    int tx = j + topx[d], ty = n - i - 1 - j + topy[d], bx = k + botx[d], by = n + i - 1 - k + boty[d];
                    if ((tx < 0 or ty < 0) or (bx >= n or by >= n)) continue;
                    if (arr[ty][tx] == arr[by][bx]) cur[tx][bx] = (cur[tx][bx] + prv[j][k]) % modval;
                }
            }
        }
        swap(cur, prv);
    }

    cout << prv[0][n - 1] << "\n";
	return 0;
}
