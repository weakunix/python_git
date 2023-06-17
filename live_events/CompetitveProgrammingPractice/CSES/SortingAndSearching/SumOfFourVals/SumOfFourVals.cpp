#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
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

int n, tar;
vector<int> arr;
unordered_map<int, simps> seen;

int main() {
    cin >> n >> tar;
    arr.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int curtar = tar - arr[i] - arr[j];
            if (seen.count(curtar) > 0) {
                cout << seen[curtar].first << " " << seen[curtar].second << " " << i << " " << j << "\n";
                return 0;
            }
        }
        for (int j = 1; j < i; j++) seen[arr[i] + arr[j]] = {j, i};
    }
    cout << "IMPOSSIBLE\n";
	return 0;
}
