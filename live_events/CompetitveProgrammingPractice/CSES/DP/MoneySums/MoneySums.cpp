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

int n, ans = 0;
vector<bool> seen(1e5 + 1);

int main() {
    cin >> n;
    seen[0] = true;
    for (int i = 0; i < n; i++) {
        int cur;
        vector<bool> prv = seen;
        cin >> cur;
        for (int j = 0; j <= 1e5; j++) {
            if (prv[j]) seen[j + cur] = true;
        }
    }
    for (int i = 1; i <= 1e5; i++) ans += seen[i];
    cout << ans << "\n";
    for (int i = 1; i <= 1e5; i++) {
        if (seen[i]) cout << i << " ";
    }
    cout << "\n";
	return 0;
}
