#include <iostream>
#include <iomanip>
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

const int N = 8, K = 101, dirx[4] = {1, 0, -1, 0}, diry[4] = {0, 1, 0, -1};

int k;
double dp[K][N][N][N][N], ans = 0;

int main() {
    memset(dp, 0, sizeof(dp));

    cin >> k;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) dp[0][i][j][i][j] = 1;
    }
    for (int i = 0; i < k; i++) {
        for (int y1 = 0; y1 < N; y1++) {
            for (int x1 = 0; x1 < N; x1++) {
                for (int y2 = 0; y2 < N; y2++) {
                    for (int x2 = 0; x2 < N; x2++) {
                        vector<int> psbl;
                        for (int j = 0; j < 4; j++) {
                            int newx = x2 + dirx[j], newy = y2 + diry[j];
                            if ((newx < 0 or newx >= N) or (newy < 0 or newy >= N)) continue;
                            psbl.push_back(j);
                        }
                        for (int j : psbl) dp[i + 1][y1][x1][y2 + diry[j]][x2 + dirx[j]] += dp[i][y1][x1][y2][x2] / psbl.size();
                    }
                }
            }
        }
    }
    for (int y2 = 0; y2 < N; y2++) {
        for (int x2 = 0; x2 < N; x2++) {
            double cur = 1;
            for (int y1 = 0; y1 < N; y1++) {
                for (int x1 = 0; x1 < N; x1++) cur *= (1 - dp[k][y1][x1][y2][x2]);
            }
            ans += cur;
        }
    }
    cout << fixed << setprecision(6) << ans << "\n";
	return 0;
}
