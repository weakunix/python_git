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

int ans = 0;
vector<int> x = {0, 1, 2, 3, 4, 5, 6, 7};
vector<vector<bool>> board(8, vector<bool>(8));

bool works() {
    for (int i = 0; i < 8; i++) {
        if (not board[i][x[i]]) return false;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (abs(i - j) == abs(x[i] - x[j])) return false;
        }
    }
    return true;
}

int main() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char c;
            cin >> c;
            board[i][j] = (c == '.');
        }
    }
    while (true) {
        ans += works();
        if (not next_permutation(all(x))) break;
    }
    cout << ans << "\n";
	return 0;
}
