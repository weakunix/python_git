#include <iostream>
#include <string>
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

int n;
vector<int> arr;
vector<vector<int>> rng;

int main() {
    cin >> n;
    arr.resize(n);
    rng.resize(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) cin >> rng[i][j];
    }
    for (int i = 1; i < n; i++) {
        int cur = arr[i - 1] + rng[i - 1][i], mn = cur, mx = cur;
        bool works = true;
        for (int j = i - 1; j >= 0; j--) {
            mn = min(arr[j], mn);
            mx = max(arr[j], mx);
            if (rng[j][i] != mx - mn) {
                works = false;
                break;
            }
        }
        if (works) arr[i] = cur;
        else arr[i] = arr[i - 1] - rng[i - 1][i];
    }
    for (int i = 0; i < n; i++) cout << arr[i] << ((i < n - 1) ? " " : "\n");
	return 0;
}
