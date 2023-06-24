#include <iostream>
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

int diga[20], digb[20];
ll a, b, dp[20][11][11][2][2];

void setvars() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 11; j++) {
            for (int k = 0; k < 11; k++) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 2; m++) dp[i][j][k][l][m] = -1;
                }
            }
        }
    }
}

ll getdp(int idx, int curdig, int prevdig, int islow, int ishigh) {
    if (dp[idx][curdig][prevdig][islow][ishigh] != -1) return dp[idx][curdig][prevdig][islow][ishigh];

}

int main() {
    setvars();
    cin >> a >> b;
    for (int i = 0; i < 20; i++) {
        diga[19 - i] = (a == 0) ? 10 : a % 10;
        digb[19 - i] = (b == 0) ? 10 : b % 10;
        a /= 10;
        b /= 10;
    }
    cout << getdp(0, 10, 10, 1, 1) << "\n";
	return 0;
}
